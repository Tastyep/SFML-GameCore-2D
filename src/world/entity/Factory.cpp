#include "world/entity/Factory.hpp"

#include <utility>

namespace GameCore {
namespace World {
namespace Entity {

// clang-format off
Factory::Factory(std::shared_ptr<Ressource::TileManager> tileManager,
                 std::shared_ptr<Hitbox::Manager<Tile>> hitboxManager,
                 std::shared_ptr<Input::Dispatcher<Action>> actionDispatcher)
  // clang-format on
  : _tileManager(std::move(tileManager)),
    _hitboxManager(std::move(hitboxManager)),
    _actionDispatcher(std::move(actionDispatcher)) {}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
