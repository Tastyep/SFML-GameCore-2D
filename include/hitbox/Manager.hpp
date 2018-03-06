#ifndef GAME_CORE_HITBOX_MANAGER_HPP
#define GAME_CORE_HITBOX_MANAGER_HPP

#include <cassert>
#include <unordered_map>

#include "world/WorldConstant.hpp"

#include "hitbox/detail/BoundingBoxBuilder.hpp"
#include "hitbox/detail/ContourBuilder.hpp"
#include "hitbox/detail/CoordinateTransformer.hpp"
#include "hitbox/detail/PolygonBuilder.hpp"
#include "hitbox/detail/PolygonPartitioner.hpp"

#include "PlayRho/Collision/Shapes/PolygonShape.hpp"
#include "PlayRho/Common/VertexSet.hpp"

namespace GameCore {
namespace Hitbox {

template <typename Identifier>
class Manager {
 private:
  using Polygon = std::vector<sf::Vector2f>;

 public:
  void load(const Identifier& id, const sf::Sprite& sprite, size_t accuracy) {
    auto contour = _contourBuilder.make(sprite);

    Detail::toCarthesian(sprite, contour);
    auto polygon = _polygonBuilder.make(contour, accuracy);
    auto polygons = _polygonPartitioner.make(std::move(polygon));

    this->translatePolygons(polygons, kSpriteOrigin);
    this->makeBody(id, polygons);
  }

  const std::vector<playrho::PolygonShape>& body(const Identifier& id) const {
    auto found = _hitboxes.find(id);
    assert(found != _hitboxes.end());

    return found->second;
  }

 private:
  void makeBody(const Identifier& id, const std::vector<Polygon>& polygons) {
    std::vector<playrho::PolygonShape> body;

    for (const auto& polygon : polygons) {
      playrho::VertexSet vertices;
      playrho::PolygonShape bodyPart;

      // NOTE: The bodies should be managed in pixel size, then adapted in the word factory.
      for (const auto& v : polygon) {
        vertices.add(playrho::Length2D{ v.x * World::kWorldScale, v.y * World::kWorldScale });
      }

      bodyPart.Set(vertices);
      body.push_back(std::move(bodyPart));
    }
    _hitboxes[id] = std::move(body);
  }

  void translatePolygons(std::vector<Polygon>& polygons, const sf::Vector2f& center) {
    for (auto& polygon : polygons) {
      for (auto& v : polygon) {
        v -= center;
      }
    }
  }

 private:
  Detail::ContourBuilder _contourBuilder;
  Detail::PolygonBuilder _polygonBuilder;
  Detail::BoundingBoxBuilder _boundingBoxBuilder;
  Detail::PolygonPartitioner _polygonPartitioner;

 private:
  std::unordered_map<Identifier, std::vector<playrho::PolygonShape>> _hitboxes;
};

} /* namespace Hitbox */
} /* namespace GameCore */

#endif
