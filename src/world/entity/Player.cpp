#include "world/entity/Player.hpp"

namespace GameCore {
namespace World {
namespace Entity {

Player::Player(Physic::CollisionBody body, const sf::Sprite& sprite)
  : Entity(std::move(body), sprite) {
  for (auto action : kActionTable) {
    _actions.emplace(action, false);
  }
}

void Player::update() {
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
