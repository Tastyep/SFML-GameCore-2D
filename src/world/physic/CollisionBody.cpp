#include "world/physic/CollisionBody.hpp"

namespace GameCore {
namespace World {
namespace Physic {

CollisionBody::CollisionBody(const sf::FloatRect& bbox, std::vector<std::vector<sf::Vector2f>> polygons) {
  for (auto&& bodyPart : polygons) {
    _body.emplace_back(std::move(bodyPart));
  }

  std::vector<sf::Vector2f> bboxVertices;
  bboxVertices.emplace_back(bbox.left, bbox.top);
  bboxVertices.emplace_back(bbox.left, bbox.top + bbox.height);
  bboxVertices.emplace_back(bbox.left + bbox.width, bbox.top + bbox.height);
  bboxVertices.emplace_back(bbox.left + bbox.width, bbox.top);
  _boundingBox = Bbox(std::move(bboxVertices));
}

void CollisionBody::draw(sf::RenderTarget& target, sf::RenderStates) const {
  target.draw(_boundingBox);
  for (const auto& bodyPart : _body) {
    target.draw(bodyPart);
  }
}

void CollisionBody::setPosition(const sf::Vector2f& position) {
  _boundingBox.setPosition(position);
  for (auto& bodyPart : _body) {
    bodyPart.setPosition(position);
  }
}

void CollisionBody::move(const sf::Vector2f& distance) {
  _boundingBox.move(distance);
  for (auto& bodyPart : _body) {
    bodyPart.move(distance);
  }
}

const CollisionBody::Bbox& CollisionBody::boundingBox() const {
  return _boundingBox;
}

const CollisionBody::Body& CollisionBody::body() const {
  return _body;
}

} /* namespace Physic */
} /* namespace World */
} /* namespace GameCore */
