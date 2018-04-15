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

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
