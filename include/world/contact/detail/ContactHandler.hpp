#ifndef GAMECORE_WORLD_CONTACT_DETAIL_CONTACT_HANDLER_HPP
#define GAMECORE_WORLD_CONTACT_DETAIL_CONTACT_HANDLER_HPP

#include "PlayRho/Dynamics/Contacts/Contact.hpp"

namespace World {
namespace Entity {

class Entity;
class Player;
class Ball;
class Wall;

} /* namespace Entity */

namespace Contact {
namespace Detail {

class Handler {
 public:
  void handle(Entity::Entity& a, Entity::Entity& b, playrho::Contact& contact) const;
  void handle(Entity::Wall& wall, Entity::Ball& ball, playrho::Contact& contact) const;
  void handle(Entity::Wall& wall, Entity::Player& player, playrho::Contact& contact) const;
  void handle(Entity::Ball& a, Entity::Ball& b, playrho::Contact& contact) const;
  void handle(Entity::Ball& ball, Entity::Player& player, playrho::Contact& contact) const;
  void handle(Entity::Player& a, Entity::Player& b, playrho::Contact& contact) const;
};

} /* namespace Detail */
} /* namespace Contact */
} /* namespace World */

#endif
