#ifndef GAME_CORE_WORLD_ENTITY_WALL_HPP
#define GAME_CORE_WORLD_ENTITY_WALL_HPP

#include "world/entity/Entity.hpp"

namespace World {
namespace Entity {

class Wall : public Entity {
 public:
  Wall(playrho::Body* body, const sf::Sprite& sprite, const App::Command::Dispatcher& commandDispatcher);

  void update() override;
  Id id() const override;
};

} /* namespace Entity */
} /* namespace World */

#endif
