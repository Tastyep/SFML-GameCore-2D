#include "world/physic/CollisionBody.hpp"

namespace GameCore {
namespace World {
namespace Physic {

CollisionBody::CollisionBody(const sf::Rect<int>& bbox, const std::vector<std::vector<sf::Vector2i>>& polygons) {
  for (size_t i = 0; i < polygons.size(); ++i) {
    const auto& polygon = polygons[i];
    std::vector<sf::Vector2f> bodyPart;

    std::transform(polygon.begin(), polygon.end(), std::back_inserter(bodyPart),
                   [](const auto& vertice) { return static_cast<sf::Vector2f>(vertice); });
    _body.emplace_back(std::move(bodyPart));
  }

  std::vector<sf::Vector2f> bboxVertices;
  bboxVertices.emplace_back(static_cast<float>(bbox.left), static_cast<float>(bbox.top));
  bboxVertices.emplace_back(static_cast<float>(bbox.left), static_cast<float>(bbox.top + bbox.height));
  bboxVertices.emplace_back(static_cast<float>(bbox.left + bbox.width), static_cast<float>(bbox.top + bbox.height));
  bboxVertices.emplace_back(static_cast<float>(bbox.left + bbox.width), static_cast<float>(bbox.top));
  _boundingBox = Bbox(std::move(bboxVertices));
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
