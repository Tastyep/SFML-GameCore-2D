#ifndef GAMECORE_WORLD_CONTACT_HANDLER_HPP
#define GAMECORE_WORLD_CONTACT_HANDLER_HPP

namespace GameCore {
namespace World {
namespace Entity {

class Entity;
class Player;
class Ball;
class Wall;

} /* namespace Entity */

class ContactHandler {
 public:
  void dispatch(Entity::Entity& entityA, Entity::Entity& entityB) const;

  void handle(Entity::Entity& entityA, Entity::Entity& entityB) const;
  void handle(Entity::Player& player, Entity::Ball& ball) const;
  void handle(Entity::Player& player, Entity::Wall& wall) const;
  void handle(Entity::Ball& ball, Entity::Wall& wall) const;
  void handle(Entity::Ball& ballA, Entity::Ball& ballB) const;
};

} /* namespace World */
} /* namespace GameCore */

#endif
