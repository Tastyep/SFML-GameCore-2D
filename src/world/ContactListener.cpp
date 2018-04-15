#include "world/ContactListener.hpp"

#include "PlayRho/Dynamics/Body.hpp"

#include "world/ContactResolver.hpp"

namespace GameCore {
namespace World {

void ContactListener::BeginContact(playrho::Contact& contact) {
  auto* entityA = static_cast<Entity::Entity*>(contact.GetFixtureA()->GetBody()->GetUserData());
  auto* entityB = static_cast<Entity::Entity*>(contact.GetFixtureB()->GetBody()->GetUserData());
  // const auto posA = contact.GetFixtureA()->GetBody()->GetLocation();
  // const auto posB = contact.GetFixtureB()->GetBody()->GetLocation();

  resolveContact(entityA, entityB, _contactHandler);
  // _contactHandler.dispatch(entityA, entityB /*, *contact*/);
}

void ContactListener::EndContact(playrho::Contact& contact) {}

void ContactListener::PreSolve(playrho::Contact& contact, const playrho::Manifold& oldManifold) {}

void ContactListener::PostSolve(playrho::Contact& contact, const playrho::ContactImpulsesList& impulseList,
                                playrho::ContactListener::iteration_type it) {}

} /* namespace World */
} /* namespace GameCore */
