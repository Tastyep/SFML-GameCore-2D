#include "world/entity/Player.hpp"

#include "app/command/EntityCommands.hpp"

#include "world/WorldConstant.hpp"

#include "world/entity/Ball.hpp"

namespace GameCore {
namespace World {
namespace Entity {

constexpr std::initializer_list<Action> Player::actionTable;

Player::Player(playrho::Body* body, const sf::Sprite& sprite, const App::Command::Dispatcher& commandDispatcher)
  : Entity(std::move(body), sprite, commandDispatcher) {
  for (auto action : actionTable) {
    _actions.emplace(action, false);
  }
}

void Player::update() {
  auto moveSide = _actions[Action::UP] - _actions[Action::DOWN];
  auto rotateSide = _actions[Action::RIGHT] - _actions[Action::LEFT];

  _body->SetVelocity(playrho::Velocity{ playrho::LinearVelocity2D{ 0, 0 }, playrho::GetAngularVelocity(*_body) });

  if (moveSide != 0) {
    this->move(moveSide);
  }
  if (rotateSide != 0) {
    this->rotate(kRotationAngle * rotateSide);
  }
  if (_actions[Action::USE]) {
    this->fire();
  }
  for (const auto action : actionTable) {
    _actions[action] = false;
  }
}

void Player::handle(Action action) {
  _actions[action] = true;
}

Id Player::id() const {
  return Id::Player;
}

// Private functions

void Player::fire() {
  const auto direction = this->direction();
  auto position = _body->GetLocation();

  position += direction * (kTileSize * kWorldScale);
  _commandDispatcher.dispatch(App::Command::AddEntity(Id::Ball, position, direction * 8));
}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
