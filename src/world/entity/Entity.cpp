#include "world/entity/Entity.hpp"

#include <utility>

namespace GameCore {
namespace World {
namespace Entity {

Entity::Entity(Physic::CollisionBody body, const sf::Sprite& sprite)
  : _body(std::move(body))
  , _sprite(sprite) {}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates) const {
  target.draw(_sprite);
  target.draw(_body);
}

void Entity::setPosition(const sf::Vector2f& position) {
  _body.setPosition(position);
  _sprite.setPosition(position);
  _position = position;
}

void Entity::move(const sf::Vector2f& distance) {
  _body.move(distance);
  _sprite.move(distance);
  _position += distance;
}

const Physic::CollisionBody& Entity::body() const {
  return _body;
}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
