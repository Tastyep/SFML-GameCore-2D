#ifndef GAME_CORE_WORLD_ENTITY_ENTITY_HPP
#define GAME_CORE_WORLD_ENTITY_ENTITY_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Box2D/Dynamics/b2Body.h"

#include "world/physic/CollisionBody.hpp"

namespace GameCore {
namespace World {
namespace Entity {

class Entity : public sf::Drawable {
 public:
  Entity(b2Body* body, const sf::Sprite& sprite);
  virtual ~Entity() = default;
  virtual void update() = 0;
  virtual bool moves() const = 0;

 public:
  void draw(sf::RenderTarget& target, sf::RenderStates) const override;

 public:
  void move(int direction);
  void rotate(int degrees);

 public:
  const b2Body& body() const;

 protected:
  sf::Vector2f _position;

 private:
  b2Body* _body;
  mutable sf::Sprite _sprite;
};

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */

#endif
