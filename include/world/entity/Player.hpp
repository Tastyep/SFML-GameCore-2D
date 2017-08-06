#ifndef GAME_CORE_WORLD_ENTITY_PLAYER_HPP
#define GAME_CORE_WORLD_ENTITY_PLAYER_HPP

#include "world/entity/Movable.hpp"

#include <initializer_list>
#include <unordered_map>

#include "Action.hpp"
#include "input/ActionHandler.hpp"

namespace GameCore {
namespace World {
namespace Entity {

class Player : public Movable, public Input::ActionHandler<Action> {
 public:
  // clang-format off
 const std::initializer_list<Action> kActionTable = {
    Action::USE,
    Action::LEFT,
    Action::RIGHT,
    Action::UP,
    Action::DOWN,
    Action::JUMP,
  };
  // clang-format on

 public:
  Player(Physic::CollisionBody body, const sf::Sprite& sprite);

  void update() override;
  bool moves() const override {
    return true;
  }

  void handle(Action action);

 private:
  float kRotationAngle = 5;

 private:
  std::unordered_map<Action, bool> _actions;
};

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */

#endif
