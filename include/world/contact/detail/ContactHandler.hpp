#ifndef GAMECORE_WORLD_CONTACT_DETAIL_CONTACT_HANDLER_HPP
#define GAMECORE_WORLD_CONTACT_DETAIL_CONTACT_HANDLER_HPP

namespace GameCore {
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
  void handle(Entity::Entity& a, Entity::Entity& b) const;
  void handle(Entity::Wall& wall, Entity::Ball& ball) const;
  void handle(Entity::Wall& wall, Entity::Player& player) const;
  void handle(Entity::Ball& a, Entity::Ball& b) const;
  void handle(Entity::Ball& ball, Entity::Player& player) const;
  void handle(Entity::Player& a, Entity::Player& b) const;
};

} /* namespace Detail */
} /* namespace Contact */
} /* namespace World */
} /* namespace GameCore */

#endif
