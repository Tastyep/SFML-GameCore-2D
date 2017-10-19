#include "world/entity/Entity.hpp"

#include <iostream>
#include <utility>

#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include "GameConstant.hpp"

namespace GameCore {
namespace World {
namespace Entity {

Entity::Entity(b2Body* body, const sf::Sprite& sprite)
  : _body(std::move(body))
  , _sprite(sprite) {
  _body->SetUserData(this);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates) const {
  const auto wPosition = _body->GetPosition();
  const auto bodyAngle = _body->GetAngle();

  _sprite.setPosition(sf::Vector2f(wPosition.x * kWorldScale, wPosition.y * kWorldScale));
  _sprite.setRotation(bodyAngle);

  target.draw(_sprite);
}

void Entity::move(int direction) {
  float wAngle = _body->GetAngle();
  float force = direction * 5;
  b2Vec2 wDirection = { std::cos(wAngle) * force, std::sin(wAngle) * force };

  std::cout << "wAngle: " << wDirection.x << " " << wDirection.y << std::endl;
  _body->SetLinearVelocity(wDirection);
}

void Entity::rotate(int angle) {
  float bodyAngle = _body->GetAngle();
  std::cout << "bodyAngle: " << bodyAngle << std::endl;
  bodyAngle += angle;

  _body->SetTransform(_body->GetPosition(), bodyAngle);
}

const b2Body& Entity::body() const {
  return *_body;
}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
