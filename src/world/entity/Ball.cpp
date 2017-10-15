#include "world/entity/Ball.hpp"

namespace GameCore {
namespace World {
namespace Entity {

Ball::Ball(b2Body* body, const sf::Sprite& sprite)
  : Entity(std::move(body), sprite) {}

void Ball::update() {}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
