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

#include "app/command/CommandDispatcher.hpp"

#include "hitbox/Manager.hpp"
#include "input/Dispatcher.hpp"
#include "ressource/TileManager.hpp"
#include "util/EnumCast.hpp"

#include "world/WorldConstant.hpp"
#include "world/entity/Ball.hpp"
#include "world/entity/EntityId.hpp"
#include "world/entity/Player.hpp"
#include "world/entity/Wall.hpp"

#include "boost/hana/at_key.hpp"
#include "boost/hana/integral_constant.hpp"
#include "boost/hana/map.hpp"
#include "boost/hana/pair.hpp"
#include "boost/hana/type.hpp"

namespace hana = boost::hana;

namespace World {
namespace Entity {

class Factory {
 public:
  Factory(std::shared_ptr<Ressource::TileManager> tileManager, std::shared_ptr<Hitbox::Manager> hitboxManager,
          std::shared_ptr<Input::Dispatcher<Action>> actionDispatcher,
          const App::Command::Dispatcher& commandDispatcher)
    : _tileManager(std::move(tileManager))
    , _hitboxManager(std::move(hitboxManager))
    , _actionDispatcher(std::move(actionDispatcher))
    , _commandDispatcher(commandDispatcher) {}

  template <typename... Args>
  std::shared_ptr<Entity> make(Id entityId, playrho::BodyDef bodyDef, Args... args) const {
    switch (entityId) {
    case Id::Wall: return this->make<Wall>(bodyDef, std::forward<Args>(args)...);
    case Id::Ball: return this->make<Ball>(bodyDef, std::forward<Args>(args)...);
    case Id::Player: return this->make<Player>(bodyDef, std::forward<Args>(args)...);
    }
    return nullptr;
  }

  void setWorld(std::shared_ptr<playrho::World> world) {
    _world = std::move(world);
  }

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

    std::shared_ptr<Entity> operator()(playrho::BodyDef bodyDef, Args... args) const {
      return _factory.init<Entity>(bodyDef, std::forward<Args>(args)...);
    }
  };

  template <typename... Args>
  struct Maker<Player, Args...> : public MakerBase {
    using MakerBase::MakerBase;

    std::shared_ptr<Player> operator()(playrho::BodyDef bodyDef, Args... args) const {
      auto player = _factory.init<Player>(bodyDef, std::forward<Args>(args)...);

      _factory._actionDispatcher->registerHandler(player->actionTable, player);
      return player;
    }
  };

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
  std::shared_ptr<Entity> make(playrho::BodyDef bodyDef, Args... args) const {
    return Maker<Entity, Args...>(*this)(bodyDef, std::forward<Args>(args)...);
  }

  template <typename Entity, typename... Args>
  std::shared_ptr<Entity> init(playrho::BodyDef bodyDef, Args... args) const {
    auto tileId = tile<Entity>();
    auto sprite = _tileManager->tile(tileId);
    const auto position = bodyDef.location;

    bodyDef.UseType(bodyType<Entity>());
    sprite.setOrigin(kSpriteOrigin);
    sprite.setPosition(sf::Vector2f{ position[0], position[1] } * static_cast<float>(kTileSize));

    playrho::Body* body(_world->CreateBody(bodyDef));
    const auto polyShapes = _hitboxManager->body(static_cast<size_t>(tileId));
    for (const auto& shapeConf : polyShapes) {
      const auto shape = std::make_shared<playrho::PolygonShape>(shapeConf);
      body->CreateFixture(shape);
    }

    return std::make_shared<Entity>(std::move(body), sprite, _commandDispatcher, std::forward<Args>(args)...);
  }

 private:
  std::shared_ptr<Ressource::TileManager> _tileManager;
  std::shared_ptr<Hitbox::Manager> _hitboxManager;
  std::shared_ptr<Input::Dispatcher<Action>> _actionDispatcher;
  const App::Command::Dispatcher& _commandDispatcher;
  std::shared_ptr<playrho::World> _world{ nullptr };
};

} /* namespace Entity */
} /* namespace World */

#endif
