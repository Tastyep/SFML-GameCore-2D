#include "world/ContactListener.hpp"

#include <iostream>

namespace GameCore {
namespace World {

void ContactListener::BeginContact(playrho::Contact& contact) {
  auto& entityA = *static_cast<Entity::Entity*>(contact.GetFixtureA()->GetBody()->GetUserData());
  auto& entityB = *static_cast<Entity::Entity*>(contact.GetFixtureB()->GetBody()->GetUserData());
  std::cout << "BeginContact" << std::endl;

  // _contactDispatcher.dispatch(entityA, entityB, *contact) || _contactDispatcher.dispatch(entityB, entityA, *contact);
}

void ContactListener::EndContact(playrho::Contact& contact) {
  std::cout << "EndContact" << std::endl;
}

void ContactListener::PreSolve(playrho::Contact& contact, const playrho::Manifold& oldManifold) {}

void ContactListener::PostSolve(playrho::Contact& contact, const playrho::ContactImpulsesList& impulseList,
                                playrho::ContactListener::iteration_type it) {}

} /* namespace World */
} /* namespace GameCore */
