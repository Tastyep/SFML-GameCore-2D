#include "world/entity/Wall.hpp"

#include "world/entity/Ball.hpp"
#include "world/entity/Player.hpp"

namespace GameCore {
namespace World {
namespace Entity {

Wall::Wall(playrho::Body* body, const sf::Sprite& sprite)
  : Entity(std::move(body), sprite) {}

void Wall::dispatchContact(const ContactHandler& handler, Entity& entity) {
  entity.dispatchContact(*this, handler);
}

void Wall::dispatchContact(Player& player, const ContactHandler& handler) {
  handler.handle(player, *this);
}

void Wall::dispatchContact(Ball& ball, const ContactHandler& handler) {
  handler.handle(ball, *this);
}

void Wall::update() {}

const std::string& Wall::name() const {
  return _name;
}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
