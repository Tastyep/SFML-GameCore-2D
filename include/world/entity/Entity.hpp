#ifndef GAME_CORE_WORLD_ENTITY_ENTITY_HPP
#define GAME_CORE_WORLD_ENTITY_ENTITY_HPP

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "world/physic/CollisionBody.hpp"

namespace GameCore {
namespace World {
namespace Entity {

class Entity : public sf::Drawable {
 public:
  Entity(Physic::CollisionBody body, const sf::Sprite& sprite);

  virtual void update() = 0;
  virtual bool moves() const = 0;

 public:
  void draw(sf::RenderTarget& target, sf::RenderStates) const override;

 public:
  void setPosition(const sf::Vector2f& position);
  void move(const sf::Vector2f& distance);

 public:
  const Physic::CollisionBody& body() const;

 protected:
  sf::Vector2f _position;

 private:
  Physic::CollisionBody _body;
  sf::Sprite _sprite;
};

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */

#endif
