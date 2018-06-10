#ifndef GAME_CORE_HITBOX_MANAGER_HPP
#define GAME_CORE_HITBOX_MANAGER_HPP

#include <cassert>
#include <unordered_map>

#include "world/WorldConstant.hpp"

#include "HitboxBuilder/Module.hpp"
#include "HitboxBuilder/Types.hpp"

#include "PlayRho/Collision/Shapes/PolygonShape.hpp"
#include "PlayRho/Common/VertexSet.hpp"

namespace Hitbox {

class Manager {
 private:
  using Polygon = ::HitboxBuilder::Polygon;

 public:
  Manager();

 public:
  void load(size_t id, const sf::Sprite& sprite, size_t accuracy);
  const std::vector<playrho::PolygonShape>& body(size_t id) const;

 private:
  void makeBody(size_t id, const std::vector<Polygon>& polygons);
  void translatePolygons(std::vector<Polygon>& polygons, const sf::Vector2i& center) const;

 private:
  std::unordered_map<size_t, std::vector<playrho::PolygonShape>> _hitboxes;
};

} /* namespace Hitbox */

#endif
