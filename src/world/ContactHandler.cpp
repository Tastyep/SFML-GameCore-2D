#include "world/ContactHandler.hpp"

#include <cassert>

#include "world/entity/Ball.hpp"
#include "world/entity/Player.hpp"
#include "world/entity/Wall.hpp"

namespace GameCore {
namespace World {

void ContactHandler::dispatch(Entity::Entity& entityA, Entity::Entity& entityB) const {
  entityA.dispatchContact(*this, entityB);
}

void ContactHandler::handle(Entity::Entity& entityA, Entity::Entity& entityB) const {
  // Implement a name method for entities & improve the message bellow.
  assert("missing contact handler");
}

void ContactHandler::handle(Entity::Player& player, Entity::Ball& ball) const {
  std::cout << "player ball contact" << std::endl;
}

void ContactHandler::handle(Entity::Player& player, Entity::Wall& wall) const {
  std::cout << "player wall contact" << std::endl;
}

void ContactHandler::handle(Entity::Ball& ball, Entity::Wall& wall) const {
  std::cout << "Ball Wall contact" << std::endl;
}

void ContactHandler::handle(Entity::Ball& ballA, Entity::Ball& ballB) const {
  std::cout << "Ball Ball contact" << std::endl;
}

} /* namespace World */
} /* namespace GameCore */
