#include "world/entity/Player.hpp"

#include "world/entity/Ball.hpp"
#include "world/entity/Wall.hpp"

namespace GameCore {
namespace World {
namespace Entity {

Player::Player(playrho::Body* body, const sf::Sprite& sprite)
  : Entity(std::move(body), sprite) {
  for (auto action : kActionTable) {
    _actions.emplace(action, false);
  }
}

void Player::dispatchContact(const ContactHandler& handler, Entity& entity) {
  entity.dispatchContact(*this, handler);
}

void Player::dispatchContact(Ball& ball, const ContactHandler& handler) {
  handler.handle(*this, ball);
}

void Player::dispatchContact(Wall& wall, const ContactHandler& handler) {
  handler.handle(*this, wall);
}

void Player::update() {
  auto moveSide = _actions[Action::UP] - _actions[Action::DOWN];
  auto rotateSide = _actions[Action::LEFT] - _actions[Action::RIGHT];

  if (moveSide != 0) {
    this->move(moveSide);
  }
  if (rotateSide != 0) {
    this->rotate(kRotationAngle * rotateSide);
  }
  for (auto action : kActionTable) {
    _actions[action] = false;
  }
}

void Player::handle(Action action) {
  _actions[action] = true;
}

const std::string& Player::name() const {
  return _name;
}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
