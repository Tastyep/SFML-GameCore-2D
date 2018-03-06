#ifndef GAME_CORE_WORLD_ENTITY_ENTITY_HPP
#define GAME_CORE_WORLD_ENTITY_ENTITY_HPP

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "PlayRho/Dynamics/Body.hpp"

#include "world/ContactHandler.hpp"

namespace GameCore {
namespace World {
namespace Entity {

class Player;
class Ball;
class Wall;

class Entity : public sf::Drawable {
 public:
  Entity(playrho::Body* body, const sf::Sprite& sprite);
  virtual ~Entity() = default;

  virtual void update() = 0;
  // Get the name of the entity, used for debug.
  virtual const std::string& name() const = 0;

  // Double dispatch the contact information to get the derived entity type.
  virtual void dispatchContact(const ContactHandler& handler, Entity& entity) = 0;
  // Defines the default behaviour for unhandled contacts.
  void dispatchContact(Entity& entity, const ContactHandler& handler);

  virtual void dispatchContact(Player&, const ContactHandler&);
  virtual void dispatchContact(Wall&, const ContactHandler&);
  virtual void dispatchContact(Ball&, const ContactHandler&);

 public:
  void draw(sf::RenderTarget& target, sf::RenderStates) const override;

 public:
  void move(int direction);
  void rotate(int degrees);

 public:
  const playrho::Body& body() const;

 protected:
  sf::Vector2f _position;

 public:
  playrho::Body* _body;
  mutable sf::Sprite _sprite;
};

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */

#endif
