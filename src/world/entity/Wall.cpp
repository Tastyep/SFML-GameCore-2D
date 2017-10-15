#include "world/entity/Wall.hpp"

namespace GameCore {
namespace World {
namespace Entity {

Wall::Wall(b2Body* body, const sf::Sprite& sprite)
  : Entity(std::move(body), sprite) {}

void Wall::update() {}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
