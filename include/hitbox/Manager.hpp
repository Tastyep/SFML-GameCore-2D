#ifndef GAME_CORE_HITBOX_MANAGER_HPP
#define GAME_CORE_HITBOX_MANAGER_HPP

#include <cassert>
#include <unordered_map>

#include "GameConstant.hpp"

#include "hitbox/BoundingBoxBuilder.hpp"
#include "hitbox/ContourBuilder.hpp"
#include "hitbox/PolygonBuilder.hpp"
#include "hitbox/PolygonPartitioner.hpp"

#include "Box2D/Collision/Shapes/b2PolygonShape.h"

namespace GameCore {
namespace Hitbox {

template <typename Identifier>
class Manager {
 private:
  using Polygon = std::vector<sf::Vector2f>;

 public:
  void load(const Identifier& id, const sf::Sprite& sprite, size_t accuracy) {
    std::vector<sf::Vector2f> floatContour;
    auto contour = _contourBuilder.make(sprite);
    auto polygon = _polygonBuilder.make(contour, accuracy);

    std::transform(contour.begin(), contour.end(), std::back_inserter(floatContour),
                   [](const auto& vertice) { return static_cast<sf::Vector2f>(vertice); });
    auto boundingBox = _boundingBoxBuilder.make(floatContour);
    auto polygons = _polygonPartitioner.make(std::move(polygon));

    this->createBody(id, polygons, std::move(boundingBox));
  }

  void createBody(const Identifier& id, const std::vector<Polygon>& polygons, sf::FloatRect boundingBox) {
    std::vector<b2PolygonShape> body;

    for (const auto& polygon : polygons) {
      std::vector<b2Vec2> vertices;
      b2PolygonShape bodyPart;

      std::transform(polygon.begin(), polygon.end(), std::back_inserter(vertices),
                     [](const auto& vertice) { return b2Vec2(vertice.x / kWorldScale, vertice.y / kWorldScale); });

      bodyPart.Set(&vertices[0], vertices.size());
      body.push_back(std::move(bodyPart));
    }
    _hitboxes[id] = { std::move(body), std::move(boundingBox) };
  }

  const std::vector<b2PolygonShape>& body(const Identifier& id) const {
    auto found = _hitboxes.find(id);
    assert(found != _hitboxes.end());

    return found->second.body;
  }

  const sf::FloatRect& boundingBox(const Identifier& id) const {
    auto found = _hitboxes.find(id);
    assert(found != _hitboxes.end());

    return found->second.boundingBox;
  }

 private:
  struct Hitbox {
    std::vector<b2PolygonShape> body;
    sf::FloatRect boundingBox;
  };

 private:
  ContourBuilder _contourBuilder;
  PolygonBuilder _polygonBuilder;
  BoundingBoxBuilder _boundingBoxBuilder;
  PolygonPartitioner _polygonPartitioner;

 private:
  std::unordered_map<Identifier, Hitbox> _hitboxes;
};

} /* namespace Hitbox */
} /* namespace GameCore */

#endif
