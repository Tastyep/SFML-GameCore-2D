#ifndef GAME_CORE_WORLD_ENTITY_MOVABLE_HPP
#define GAME_CORE_WORLD_ENTITY_MOVABLE_HPP

#include "world/entity/Entity.hpp"

namespace GameCore {
namespace World {
namespace Entity {

class Movable : public Entity {
 public:
  using Entity::Entity;

  void move(int side);
  void rotate(float angle);

 protected:
  float _angle = 0;
  sf::Vector2f _direction{ 1, 0 };
  float _velocity{ 0 };
  float _acceleration{ 0.001 };
};

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */

#endif
