#include "world/ContactListener.hpp"

#include <iostream>

namespace GameCore {
namespace World {

void ContactListener::BeginContact(b2Contact* contact) {
  auto& entityA = *static_cast<Entity::Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
  auto& entityB = *static_cast<Entity::Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());
  std::cout << "BeginContact" << std::endl;

  // _contactDispatcher.dispatch(entityA, entityB, *contact) || _contactDispatcher.dispatch(entityB, entityA, *contact);
}

void ContactListener::EndContact(b2Contact* contact) {
  std::cout << "EndContact" << std::endl;
}

} /* namespace World */
} /* namespace GameCore */
