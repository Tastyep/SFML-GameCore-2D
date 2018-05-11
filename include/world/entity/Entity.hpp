#ifndef GAME_CORE_WORLD_ENTITY_ENTITY_HPP
#define GAME_CORE_WORLD_ENTITY_ENTITY_HPP

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "PlayRho/Dynamics/Body.hpp"

#include "app/command/CommandDispatcher.hpp"

#include "world/entity/EntityId.hpp"

namespace World {
namespace Entity {

class Player;
class Ball;
class Wall;

class Entity : public sf::Drawable {
 public:
  Entity(playrho::Body* body, const sf::Sprite& sprite, const App::Command::Dispatcher& commandDispatcher);
  virtual ~Entity() = default;

  virtual void update() = 0;
  virtual Id id() const = 0;

 public:
  void draw(sf::RenderTarget& target, sf::RenderStates) const override;

 public:
  void move(int direction);
  void rotate(int degrees);

 protected:
  playrho::Length2D direction() const;
  playrho::Length2D velocityDirection() const;
  float speed() const;

 protected:
  sf::Vector2f _position;

 public:
  playrho::Body* _body;
  mutable sf::Sprite _sprite;
  const App::Command::Dispatcher& _commandDispatcher;
};

} /* namespace Entity */
} /* namespace World */

#endif
