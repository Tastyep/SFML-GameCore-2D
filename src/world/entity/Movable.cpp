#include "world/entity/Movable.hpp"

#include "GameConstant.hpp"

#include <iostream>

namespace GameCore {
namespace World {
namespace Entity {

void Movable::move(int side) {
  _velocity = _velocity + (_acceleration * static_cast<float>(side)) * static_cast<float>(kTimeStep.count());
  sf::Vector2f newPosition = _position + (_velocity * _direction) * static_cast<float>(kTimeStep.count());
  sf::Vector2f translation = newPosition - _position;

  Entity::move(translation);
}

void Movable::rotate(float angle) {
  _angle = (static_cast<int>(_angle + angle) + 360) % 360;
  auto theta = _angle * M_PI / 180.f;

  _direction.x = std::cos(theta);
  _direction.y = -std::sin(theta);
  auto direction = _direction;
}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
