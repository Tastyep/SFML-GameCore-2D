#include "world/contact/ContactListener.hpp"

#include "PlayRho/Dynamics/Body.hpp"

#include "world/contact/detail/ContactResolver.hpp"

namespace GameCore {
namespace World {
namespace Contact {

void Listener::BeginContact(playrho::Contact& contact) {
  auto* entityA = static_cast<Entity::Entity*>(contact.GetFixtureA()->GetBody()->GetUserData());
  auto* entityB = static_cast<Entity::Entity*>(contact.GetFixtureB()->GetBody()->GetUserData());
  // const auto posA = contact.GetFixtureA()->GetBody()->GetLocation();
  // const auto posB = contact.GetFixtureB()->GetBody()->GetLocation();

  resolveContact(entityA, entityB, contact, _contactHandler);
  // _contactHandler.dispatch(entityA, entityB /*, *contact*/);
}

void Listener::EndContact(playrho::Contact& contact) {}

void Listener::PreSolve(playrho::Contact& contact, const playrho::Manifold& oldManifold) {}

void Listener::PostSolve(playrho::Contact& contact, const playrho::ContactImpulsesList& impulseList,
                         playrho::ContactListener::iteration_type it) {}

} /* namespace Contact */
} /* namespace World */
} /* namespace GameCore */
