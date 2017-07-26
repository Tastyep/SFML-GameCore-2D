#ifndef GAME_CORE_HITBOX_POLYGON_PARTITIONER_HPP
#define GAME_CORE_HITBOX_POLYGON_PARTITIONER_HPP

#include <stddef.h>
#include <utility>
#include <vector>

#include <SFML/System/Vector2.hpp>

#include "hitbox/Triangulator.hpp"

namespace GameCore {
namespace Hitbox {

class PolygonPartitioner {
 private:
  using Triangle = std::vector<sf::Vector2f>;
  using Polygon = std::vector<sf::Vector2f>;

 public:
  PolygonPartitioner() = default;

  std::vector<std::vector<sf::Vector2f>> make(std::vector<sf::Vector2f> polygon) const;

 private:
  std::vector<Polygon> make(std::vector<Triangle> triangles) const;
  std::pair<bool, size_t> findDiagonal(const auto& triangles, auto& polygonB, const auto& polygonA, size_t i) const;
  bool isPolygonConvex(const Polygon& polygon) const;

 private:
  Triangulator _triangulator;

 private:
  mutable size_t _polygonASize;
  mutable size_t _polygonBSize;
};

} /* namespace Hitbox */
} /* namespace GameCore */

#endif
