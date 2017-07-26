#ifndef GAME_CORE_WORLD_ENTITY_FACTORY_HPP
#define GAME_CORE_WORLD_ENTITY_FACTORY_HPP

#include <memory>
#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>

#include "Action.hpp"
#include "Tile.hpp"

#include "hitbox/Manager.hpp"
#include "input/ActionDispatcher.hpp"
#include "ressource/TileManager.hpp"
#include "util/EnumCast.hpp"

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

 public:
  Factory(std::shared_ptr<Ressource::TileManager> tileManager, std::shared_ptr<Hitbox::Manager<Tile>> hitboxManager,
          std::shared_ptr<Input::Dispatcher<Action>> actionDispatcher);

  template <typename Entity, typename... Args>
  std::shared_ptr<Entity> create(Args... args) const {
    auto tileId = FindTileId<Entity>;
    auto body = _hitboxManager->skeleton(tileId);
    auto boundingBox = _hitboxManager->boundingBox(tileId);
    auto sprite = _tileManager->tile(tileId);

    this->changeDataOrigin(body, boundingBox, sprite);

    return std::make_shared<Entity>(Physic::CollisionBody(boundingBox, std::move(body)), sprite,
                                    std::forward<Args>(args)...);
  }

 private:
  void changeDataOrigin(std::vector<std::vector<sf::Vector2f>>& body, sf::FloatRect& boundingBox,
                        sf::Sprite& sprite) const;

 private:
  std::shared_ptr<Ressource::TileManager> _tileManager;
  std::shared_ptr<Hitbox::Manager<Tile>> _hitboxManager;
  std::shared_ptr<Input::Dispatcher<Action>> _actionDispatcher;
};

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */

#endif
