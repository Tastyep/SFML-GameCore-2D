#ifndef GAME_CORE_WORLD_CONTACT_LISTENER_HPP
#define GAME_CORE_WORLD_CONTACT_LISTENER_HPP

#include "Box2D/Dynamics/b2WorldCallbacks.h"

namespace GameCore {
namespace World {

class ContactListener : public b2ContactListener {
 public:
  void BeginContact(b2Contact* contact) override;
  void EndContact(b2Contact* contact) override;
};

} /* namespace World */
} /* namespace GameCore */

#endif
