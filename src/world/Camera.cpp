#include "world/Camera.hpp"

namespace World {

Camera::Camera(const sf::FloatRect& rect) {
  this->setRect(rect);
}

const sf::FloatRect& Camera::view() const {
  return _view;
}

void Camera::setRect(const sf::FloatRect& rect) {
  _centerTranslation = { rect.width / 2.f, rect.height / 2.f };
  _view = rect;
  this->setPosition({ rect.left + _centerTranslation.x, rect.top + _centerTranslation.y });
}

void Camera::setPosition(const sf::Vector2f& pos) {
  sf::Vector2f tl = pos - _centerTranslation;

  _view.left = tl.x;
  _view.left = tl.y;
}

void Camera::move(const sf::Vector2f& distance) {
  _view.top += distance.y;
  _view.left += distance.x;
}

} /* namespace World */
