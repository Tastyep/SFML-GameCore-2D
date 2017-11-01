#include "world/entity/Ball.hpp"

#include "world/entity/Player.hpp"
#include "world/entity/Wall.hpp"

namespace GameCore {
namespace World {
namespace Entity {

Ball::Ball(playrho::Body* body, const sf::Sprite& sprite)
  : Entity(std::move(body), sprite) {}

void Ball::dispatchContact(const ContactHandler& handler, Entity& entity) {
  entity.dispatchContact(*this, handler);
}

void Ball::dispatchContact(Player& player, const ContactHandler& handler) {
  handler.handle(player, *this);
}

void Ball::dispatchContact(Wall& wall, const ContactHandler& handler) {
  handler.handle(*this, wall);
}

void Ball::update() {}

const std::string& Ball::name() const {
  return _name;
}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
