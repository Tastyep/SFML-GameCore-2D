#include "world/entity/Entity.hpp"

#include <iostream>
#include <utility>

#include "PlayRho/Common/Velocity.hpp"

#include "GameConstant.hpp"

namespace GameCore {
namespace World {
namespace Entity {

Entity::Entity(playrho::Body* body, const sf::Sprite& sprite)
  : _body(body)
  , _sprite(sprite) {
  _body->SetUserData(this);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates) const {
  const auto wPosition = _body->GetLocation();
  const auto bodyAngle = _body->GetAngle();

  _sprite.setPosition(sf::Vector2f(wPosition[0] * kWorldScale, wPosition[1] * kWorldScale));
  _sprite.setRotation(bodyAngle);

  target.draw(_sprite);
}

void Entity::move(int direction) {
  auto bodyAngle = _body->GetAngle();
  auto bodyPos = _body->GetLocation();

  bodyPos[0] += 0.1f * direction;
  bodyPos[1] += 0.1f * direction;
  _body->SetTransform(bodyPos, bodyAngle);
}

void Entity::rotate(int angle) {
  float bodyAngle = _body->GetAngle();
  std::cout << "bodyAngle: " << bodyAngle << std::endl;
  bodyAngle += angle;

  _body->SetTransform(_body->GetLocation(), bodyAngle);
}

const playrho::Body& Entity::body() const {
  return *_body;
}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
