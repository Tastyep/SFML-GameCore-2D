#include "world/entity/Entity.hpp"

#include <cassert>
#include <iostream>
#include <utility>

#include "PlayRho/Common/Velocity.hpp"

#include "world/WorldConstant.hpp"

#include "Util.hpp"

namespace GameCore {
namespace World {
namespace Entity {

Entity::Entity(playrho::Body* body, const sf::Sprite& sprite, const App::Command::Dispatcher& commandDispatcher)
  : _body(body)
  , _sprite(sprite)
  , _commandDispatcher(commandDispatcher) {
  _body->SetUserData(this);
}

void Entity::dispatchContact(Entity&, const ContactHandler&) {
  // Improve assert message by using the entity name.
  assert("Missing contact dispatcher");
}

void Entity::dispatchContact(Player&, const ContactHandler&) {}
void Entity::dispatchContact(Wall&, const ContactHandler&) {}
void Entity::dispatchContact(Ball&, const ContactHandler&) {}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates) const {
  const auto wPosition = _body->GetLocation();
  const auto bodyAngle = _body->GetAngle();

  _sprite.setPosition(sf::Vector2f(wPosition[0], wPosition[1]) * kPixelScale + kSpriteOrigin);
  _sprite.setRotation(bodyAngle);

  target.draw(_sprite);
}

void Entity::move(int direction) {
  const auto dirVec = this->direction() * direction;

  SetLinearVelocity(*_body, playrho::LinearVelocity2D{ 7.5f * dirVec[0], 7.5f * dirVec[1] });
}

void Entity::rotate(int angle) {
  auto cuAngle = static_cast<int>(_sprite.getRotation());

  cuAngle = (360 + cuAngle + angle) % 360;
  RotateAboutLocalPoint(*_body, cuAngle, playrho::Length2D{ 0, 0 });
}

playrho::Length2D Entity::direction() const {
  const auto bodyAngle = _body->GetAngle();
  return playrho::Length2D{ std::cos(bodyAngle * rad), std::sin(bodyAngle * rad) };
}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
