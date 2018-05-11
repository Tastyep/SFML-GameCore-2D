#ifndef GAME_CORE_WORLD_CAMERA_HPP
#define GAME_CORE_WORLD_CAMERA_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace World {

class Camera {
 public:
  Camera(const sf::FloatRect& rect);

  const sf::FloatRect& view() const;

  void setRect(const sf::FloatRect& rect);
  void setPosition(const sf::Vector2f& pos);
  void move(const sf::Vector2f& distance);

 private:
  sf::FloatRect _view;
  sf::Vector2f _centerTranslation;
};

} /* namespace World */

#endif
