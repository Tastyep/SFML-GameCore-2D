#ifndef GAME_CORE_WORLD_ENTITY_PLAYER_HPP
#define GAME_CORE_WORLD_ENTITY_PLAYER_HPP

#include "world/entity/Entity.hpp"

#include <initializer_list>
#include <unordered_map>

#include "Action.hpp"
#include "input/ActionHandler.hpp"

namespace GameCore {
namespace World {
namespace Entity {

class Player : public Entity, public Input::ActionHandler<Action> {
 public:
  static constexpr std::initializer_list<Action> actionTable = {
    Action::USE, Action::LEFT, Action::RIGHT, Action::UP, Action::DOWN, Action::JUMP,
  };

 public:
  Player(playrho::Body* body, const sf::Sprite& sprite, const App::Command::Dispatcher& commandDispatcher);

  void update() override;
  void handle(Action action) override;
  Id id() const override;

 private:
  float kRotationAngle = 10;

 private:
  void fire();

 private:
  std::unordered_map<Action, bool> _actions;
};

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */

#endif
