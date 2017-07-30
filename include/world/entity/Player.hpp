#ifndef GAME_CORE_WORLD_ENTITY_PLAYER_HPP
#define GAME_CORE_WORLD_ENTITY_PLAYER_HPP

#include "world/entity/Entity.hpp"

namespace GameCore {
namespace World {
namespace Entity {

class Player : public Entity {
 public:
  Player(Physic::CollisionBody body, const sf::Sprite& sprite);

  void update() override;
  bool moves() const override {
    return true;
  }
};

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */

#endif
