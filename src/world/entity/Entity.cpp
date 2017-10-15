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
  // auto fixtures = _body->GetFixtureList();
  target.draw(_sprite);
  auto pos = _body->GetPosition();

  // auto pos = _body->GetWorldCenter();
  //
  // for (auto fixture = _body->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
  //   b2PolygonShape* shape = (b2PolygonShape*)fixture->GetShape();
  //   sf::VertexArray vArray(sf::PrimitiveType::LineStrip, 0);
  //
  //   for (size_t i = 0; i < shape->m_count; ++i) {
  //     auto v = shape->m_vertices[i];
  //     vArray.append(sf::Vertex(sf::Vector2f{ v.x * kWorldScale, v.y * kWorldScale }, sf::Color::Black));
  //   }
  //   target.draw(vArray);
  // }
}

void Entity::move(int direction) {
  auto wAngle = _body->GetAngle();
  float force = direction * 1;
  b2Vec2 wDirection = { std::cos(wAngle) * force, std::sin(wAngle) * force };

  std::cout << "wAngle: " << wDirection.x << " " << wDirection.y << std::endl;
  _body->ApplyLinearImpulseToCenter(wDirection, true);

  auto wPosition = _body->GetPosition();

  std::cout << "pos: " << wPosition.x << " " << wPosition.y << " angle " << wAngle << std::endl;
  _sprite.setPosition(sf::Vector2f(wPosition.x * kWorldScale, wPosition.y * kWorldScale));
  // _position += distance;
}

const b2Body& Entity::body() const {
  return *_body;
}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
