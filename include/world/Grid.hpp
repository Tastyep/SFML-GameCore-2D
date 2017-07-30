#ifndef GAME_CORE_WORLD_GRID_HPP
#define GAME_CORE_WORLD_GRID_HPP

#include <cstddef>
#include <memory>
#include <unordered_set>
#include <utility>
#include <vector>

#include <SFML/Graphics/Rect.hpp>

#include "world/entity/Entity.hpp"
#include "world/physic/Polygon.hpp"

namespace GameCore {
namespace World {

class Grid {
 private:
  struct Coordinate {
    size_t x;
    size_t y;

    Coordinate(size_t x, size_t y)
      : x(x)
      , y(y) {}

    bool operator==(const Coordinate& other) const {
      return y == other.y && x == other.x;
    }

    bool operator<(const Coordinate& other) const {
      return (y < other.y || (y == other.y && x < other.x));
    }
  };

 public:
  Grid(int squareSize);

  void moveEntity(const std::shared_ptr<Entity::Entity>& entity, const Physic::Polygon& prevBound,
                  const Physic::Polygon& newBound);
  std::unordered_set<std::shared_ptr<Entity::Entity>> entities(const sf::FloatRect& viewRect) const;
  void add(std::shared_ptr<Entity::Entity> entity);
  void remove(const std::shared_ptr<Entity::Entity>& entity);
  void clear();

 private:
  std::unordered_set<std::shared_ptr<Entity::Entity>> entities(const std::vector<Coordinate>& cells) const;
  void selfExpand(const Physic::Polygon& rect);
  void add(std::shared_ptr<Entity::Entity> entity, std::vector<Coordinate> cells);
  void remove(const std::shared_ptr<Entity::Entity>& entity, std::vector<Coordinate> cells);
  Physic::Polygon rectReach(const Physic::Polygon& rect) const;
  Coordinate cellIndex(const sf::Vector2f& point) const;
  std::vector<Coordinate> overlappedCells(const Physic::Polygon& rect) const;

 private:
  int _squareSize;

 private:
  size_t _width{ 0 };
  size_t _height{ 0 };
  std::vector<std::vector<std::vector<std::shared_ptr<Entity::Entity>>>> _grid;
};

} /* namespace World */
} /* namespace GameCore */

#endif
