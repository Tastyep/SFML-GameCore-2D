#include "world/entity/Factory.hpp"

#include <utility>

#include "world/WorldConstant.hpp"

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

void Factory::changeDataOrigin(std::vector<std::vector<sf::Vector2f>>& body,
                               sf::FloatRect& boundingBox,
                               sf::Sprite& sprite) const {
  for (auto& bodyPart : body) {
    for (auto& vertice : bodyPart) {
      vertice -= kEntityOrigin;
    }
  }
  boundingBox.left -= kEntityOrigin.x;
  boundingBox.top -= kEntityOrigin.y;
  sprite.setOrigin(kEntityOrigin);
}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
