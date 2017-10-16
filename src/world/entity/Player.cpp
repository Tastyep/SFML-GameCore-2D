#include "world/entity/Player.hpp"

namespace GameCore {
namespace World {
namespace Entity {

Player::Player(b2Body* body, const sf::Sprite& sprite)
  : Entity(std::move(body), sprite) {
  for (auto action : kActionTable) {
    _actions.emplace(action, false);
  }
}

void Player::update() {
  auto moveSide = _actions[Action::UP] - _actions[Action::DOWN];
  auto rotateSide = _actions[Action::LEFT] - _actions[Action::RIGHT];

  if (moveSide != 0) {
    this->move(moveSide);
  }
  // if (rotateSide != 0) {
  //   this->rotate(kRotationAngle * rotateSide);
  // }
  for (auto action : kActionTable) {
    _actions[action] = false;
  }
}

void Player::handle(Action action) {
  _actions[action] = true;
}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
