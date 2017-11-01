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
  Player(playrho::Body* body, const sf::Sprite& sprite);

  void dispatchContact(const ContactHandler& handler, Entity& entity) override;
  void dispatchContact(Ball& ball, const ContactHandler& handler);
  void dispatchContact(Wall& wall, const ContactHandler& handler);

  void update() override;
  void handle(Action action);
  const std::string& name() const;

 private:
  const std::string _name = "Player";

 private:
  float kRotationAngle = 5;

 private:
  std::unordered_map<Action, bool> _actions;
};

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */

#endif
