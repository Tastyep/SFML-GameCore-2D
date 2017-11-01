#ifndef GAME_CORE_WORLD_CONTACT_LISTENER_HPP
#define GAME_CORE_WORLD_CONTACT_LISTENER_HPP

#include "PlayRho/Dynamics/Contacts/Contact.hpp"
#include "PlayRho/Dynamics/WorldCallbacks.hpp"

#include "world/ContactHandler.hpp"

namespace GameCore {
namespace World {

class ContactListener : public playrho::ContactListener {
 public:
  void BeginContact(playrho::Contact& contact) override;
  void EndContact(playrho::Contact& contact) override;

  void PreSolve(playrho::Contact& contact, const playrho::Manifold& oldManifold) override;
  void PostSolve(playrho::Contact& contact, const playrho::ContactImpulsesList& impulseList,
                 playrho::ContactListener::iteration_type it) override;

 private:
  ContactHandler _contactHandler;
};

} /* namespace World */
} /* namespace GameCore */

#endif
