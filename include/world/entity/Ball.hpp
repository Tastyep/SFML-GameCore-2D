#ifndef GAME_CORE_WORLD_ENTITY_BALL_HPP
#define GAME_CORE_WORLD_ENTITY_BALL_HPP

#include "PlayRho/Common/Math.hpp"

#include "world/entity/Entity.hpp"

namespace GameCore {
namespace World {
namespace Entity {

class Ball : public Entity {
 public:
  Ball(playrho::Body* body, const sf::Sprite& sprite, const App::Command::Dispatcher& commandDispatcher);

  void update() override;
  Id id() const override;

  void bounce(const playrho::UnitVec2& normal);
};

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */

#endif
