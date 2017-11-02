#ifndef GAME_CORE_WORLD_ENTITY_FACTORY_HPP
#define GAME_CORE_WORLD_ENTITY_FACTORY_HPP

#include <memory>
#include <utility>

#include "PlayRho/Dynamics/Body.hpp"
#include "PlayRho/Dynamics/BodyDef.hpp"
#include "PlayRho/Dynamics/BodyType.hpp"
#include "PlayRho/Dynamics/World.hpp"

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

#include "boost/hana/at_key.hpp"
#include "boost/hana/integral_constant.hpp"
#include "boost/hana/map.hpp"
#include "boost/hana/pair.hpp"
#include "boost/hana/type.hpp"

namespace hana = boost::hana;

namespace GameCore {
namespace World {
namespace Entity {

class Factory {
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

  void setWorld(std::shared_ptr<playrho::World> world) {
    _world = std::move(world);
  }

  template <typename Entity, typename... Args>
  std::shared_ptr<Entity> create(const sf::Vector2f& position, Args... args) const {
    return Maker<Entity, Args...>(*this)(position, std::forward<Args>(args)...);
  }

 private:
  template <typename Entity>
  constexpr Tile tile() const {
    const auto tileIds = hana::make_map(hana::make_pair(hana::type_c<Player>, hana::int_c<enum_cast(Tile::PLAYER)>),
                                        hana::make_pair(hana::type_c<Ball>, hana::int_c<enum_cast(Tile::BALL)>),
                                        hana::make_pair(hana::type_c<Wall>, hana::int_c<enum_cast(Tile::WALL)>));

    return static_cast<Tile>(hana::value(tileIds[hana::type_c<Entity>]));
  }

  template <typename Entity>
  constexpr playrho::BodyType bodyType() const {
    const auto bodies =
      hana::make_map(hana::make_pair(hana::type_c<Player>, hana::int_c<enum_cast(playrho::BodyType::Dynamic)>),
                     hana::make_pair(hana::type_c<Ball>, hana::int_c<enum_cast(playrho::BodyType::Dynamic)>),
                     hana::make_pair(hana::type_c<Wall>, hana::int_c<enum_cast(playrho::BodyType::Static)>));

    return static_cast<playrho::BodyType>(hana::value(bodies[hana::type_c<Entity>]));
  }

 private:
  template <typename Entity, typename... Args>
  std::shared_ptr<Entity> init(const sf::Vector2f& position, Args... args) const {
    auto tileId = tile<Entity>();
    auto sprite = _tileManager->tile(tileId);

    playrho::BodyDef bodyDef;
    bodyDef.UseType(bodyType<Entity>());
    bodyDef.UseLocation(playrho::Length2D(position.x / kWorldScale, position.y / kWorldScale));
    sprite.setPosition(position);

    playrho::Body* body(_world->CreateBody(bodyDef));

    auto polyShapes = _hitboxManager->body(tileId);
    for (const auto& polyShape : polyShapes) {
      const auto shape = std::make_shared<playrho::PolygonShape>();

      *shape = polyShape;
      shape->SetDensity(1);
      body->CreateFixture(shape);
    }

    return std::make_shared<Entity>(std::move(body), sprite, std::forward<Args>(args)...);
  }

 private:
  std::shared_ptr<Ressource::TileManager> _tileManager;
  std::shared_ptr<Hitbox::Manager<Tile>> _hitboxManager;
  std::shared_ptr<Input::Dispatcher<Action>> _actionDispatcher;
  std::shared_ptr<playrho::World> _world{ nullptr };
};

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */

#endif
