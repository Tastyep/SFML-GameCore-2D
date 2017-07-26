#include "world/entity/Player.hpp"

namespace GameCore {
namespace World {
namespace Entity {

Player::Player(Physic::CollisionBody body, const sf::Sprite& sprite)
  : Entity(std::move(body), sprite) {}

void Player::update() {}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
