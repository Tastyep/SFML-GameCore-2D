#include "world/entity/Wall.hpp"

namespace GameCore {
namespace World {
namespace Entity {

Wall::Wall(Physic::CollisionBody body, const sf::Sprite& sprite)
  : Entity(std::move(body), sprite) {}

void Wall::update() {}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
