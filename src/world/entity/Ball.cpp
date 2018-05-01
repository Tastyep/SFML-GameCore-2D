#include "world/entity/Ball.hpp"

namespace GameCore {
namespace World {
namespace Entity {

Ball::Ball(playrho::Body* body, const sf::Sprite& sprite, const App::Command::Dispatcher& commandDispatcher)
  : Entity(std::move(body), sprite, commandDispatcher) {}

void Ball::update() {}

Id Ball::id() const {
  return Id::Ball;
}

void Ball::bounce(const playrho::UnitVec2& normal) {
  const auto dir = this->velocityDirection();
  const auto speed = this->speed();

  const auto reflect = dir - 2 * playrho::Dot(dir, normal) * normal;

  SetLinearVelocity(*_body, reflect * speed);
}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
