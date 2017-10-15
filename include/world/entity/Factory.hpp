#ifndef GAME_CORE_WORLD_ENTITY_FACTORY_HPP
#define GAME_CORE_WORLD_ENTITY_FACTORY_HPP

#include <memory>
#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>

#include "Box2D/Box2D.h"

#include "Action.hpp"
#include "Tile.hpp"

#include "hitbox/Manager.hpp"
#include "input/ActionDispatcher.hpp"
#include "ressource/TileManager.hpp"
#include "util/EnumCast.hpp"

#include "world/WorldConstant.hpp"
#include "world/entity/Ball.hpp"
#include "world/entity/Player.hpp"
#include "world/entity/Wall.hpp"
#include "world/physic/CollisionBody.hpp"

namespace mpl = boost::mpl;

namespace GameCore {
namespace World {
namespace Entity {

class Factory {
 private:
  // clang-format off
  using EntityMap =
    mpl::map<
      mpl::pair<
        Player,
        mpl::int_<enum_cast(Tile::PLAYER)>
      >,
      mpl::pair<
        Wall,
        mpl::int_<enum_cast(Tile::WALL)>
      >,
      mpl::pair<
        Ball,
        mpl::int_<enum_cast(Tile::BALL)>
      >
    >;
  // clang-format on

  template <typename Entity>
  static constexpr Tile FindTileId = static_cast<Tile>(mpl::at<EntityMap, Entity>::type::value);

 private:
  struct MakerBase {
    MakerBase(const Factory& factory)
      : _factory(factory) {}

   protected:
    const Factory& _factory;
  };
  template <typename Entity, typename... Args>
  struct Maker : public MakerBase {
    using MakerBase::MakerBase;

    std::shared_ptr<Entity> operator()(const sf::Vector2f& position, Args... args) const {
      return _factory.init<Entity>(position, std::forward<Args>(args)...);
    }
  };

  template <typename... Args>
  struct Maker<Player, Args...> : public MakerBase {
    using MakerBase::MakerBase;

    std::shared_ptr<Player> operator()(const sf::Vector2f& position, Args... args) const {
      auto player = _factory.init<Player>(position, std::forward<Args>(args)...);

      _factory._actionDispatcher->registerHandler(player->kActionTable, player);
      return player;
    }
  };

 public:
  Factory(std::shared_ptr<Ressource::TileManager> tileManager, std::shared_ptr<Hitbox::Manager<Tile>> hitboxManager,
          std::shared_ptr<Input::Dispatcher<Action>> actionDispatcher)
    : _tileManager(std::move(tileManager))
    , _hitboxManager(std::move(hitboxManager))
    , _actionDispatcher(std::move(actionDispatcher)) {}

  void setWorld(std::shared_ptr<b2World> world) {
    _world = std::move(world);
  }

  template <typename Entity, typename... Args>
  std::shared_ptr<Entity> create(const sf::Vector2f& position, Args... args) const {
    return Maker<Entity, Args...>(*this)(position, std::forward<Args>(args)...);
  }

 private:
  template <typename Entity, typename... Args>
  std::shared_ptr<Entity> init(const sf::Vector2f& position, Args... args) const {
    auto tileId = FindTileId<Entity>;
    auto sprite = _tileManager->tile(tileId);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x / kWorldScale, position.y / kWorldScale);
    sprite.setPosition(position);
    this->changeDataOrigin(sprite);

    b2Body* body(_world->CreateBody(&bodyDef));

    auto polyShapes = _hitboxManager->body(tileId);
    for (const auto& polyShape : polyShapes) {
      b2FixtureDef fixtureDef;

      fixtureDef.shape = &polyShape;
      fixtureDef.density = 1;
      body->CreateFixture(&fixtureDef);
    }

    return std::make_shared<Entity>(std::move(body), sprite, std::forward<Args>(args)...);
  }

 private:
  void changeDataOrigin(sf::Sprite& sprite) const {
    // for (auto& bodyPart : body) {
    //   for (auto& vertice : bodyPart) {
    //     vertice -= kEntityOrigin;
    //   }
    // }
    // boundingBox.left -= kEntityOrigin.x;
    // boundingBox.top -= kEntityOrigin.y;
    // sprite.setOrigin(kEntityOrigin);
  }

 private:
  std::shared_ptr<Ressource::TileManager> _tileManager;
  std::shared_ptr<Hitbox::Manager<Tile>> _hitboxManager;
  std::shared_ptr<Input::Dispatcher<Action>> _actionDispatcher;
  std::shared_ptr<b2World> _world{ nullptr };
};

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */

#endif
