#ifndef GAME_CORE_WORLD_ENTITY_WALL_HPP
#define GAME_CORE_WORLD_ENTITY_WALL_HPP

#include "world/entity/Entity.hpp"

namespace GameCore {
namespace World {
namespace Entity {

class Wall : public Entity {
 public:
  Wall(Physic::CollisionBody body, const sf::Sprite& sprite);

  void update() override;
};

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */

#endif
