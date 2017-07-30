#include "world/Grid.hpp"

#include <algorithm>
#include <cassert>

namespace GameCore {
namespace World {

Grid::Grid(int squareSize)
  : _squareSize(squareSize) {}

void Grid::moveEntity(const std::shared_ptr<Entity::Entity>& entity, const Physic::Polygon& prevBound,
                      const Physic::Polygon& newBound) {
  const auto prevOverlap = this->overlappedCells(this->rectReach(prevBound));
  const auto newOverlap = this->overlappedCells(this->rectReach(newBound));
  std::vector<Coordinate> diff;
  std::vector<Coordinate> prevInter;
  std::vector<Coordinate> newInter;

  if (prevOverlap == newOverlap) {
    return;
  }

  std::set_difference(prevOverlap.begin(), prevOverlap.end(), newOverlap.begin(), newOverlap.end(),
                      std::inserter(diff, diff.begin()));
  std::set_intersection(diff.begin(), diff.end(), prevOverlap.begin(), prevOverlap.end(),
                        std::back_inserter(prevInter));
  std::set_intersection(diff.begin(), diff.end(), newOverlap.begin(), newOverlap.end(), std::back_inserter(newInter));

  this->selfExpand(newBound);
  this->add(entity, std::move(newInter));
  this->remove(entity, std::move(prevInter));
}

std::unordered_set<std::shared_ptr<Entity::Entity>> Grid::entities(const Physic::Polygon& viewRect) const {
  auto cells = this->overlappedCells(this->rectReach(viewRect));

  return this->entities(cells);
}

void Grid::add(std::shared_ptr<Entity::Entity> entity) {
  auto overlap = this->overlappedCells(this->rectReach(entity->body().boundingBox()));

  this->selfExpand(entity->body().boundingBox());
  this->add(std::move(entity), std::move(overlap));
}

void Grid::add(std::shared_ptr<Entity::Entity> entity, std::vector<Coordinate> cells) {
  for (auto coor : cells) {
    _grid[coor.y][coor.x].push_back(std::move(entity));
  }
}

void Grid::remove(const std::shared_ptr<Entity::Entity>& entity) {
  auto overlap = this->overlappedCells(this->rectReach(entity->body().boundingBox()));

  this->remove(entity, std::move(overlap));
}

void Grid::remove(const std::shared_ptr<Entity::Entity>& entity, std::vector<Coordinate> cells) {
  for (auto coor : cells) {
    auto& entities = _grid[coor.y][coor.x];
    auto it = std::find_if(entities.begin(), entities.end(),
                           [&entity](const auto& cEntity) { return entity.get() == cEntity.get(); });

    if (it != entities.end()) {
      entities.erase(it);
    }
  }
}

void Grid::clear() {
  _grid.clear();
}

std::unordered_set<std::shared_ptr<Entity::Entity>> Grid::entities(const std::vector<Coordinate>& cells) const {
  std::unordered_set<std::shared_ptr<Entity::Entity>> uniqueEntities;

  for (auto coor : cells) {
    const auto& entities = _grid[coor.y][coor.x];
    uniqueEntities.insert(entities.begin(), entities.end());
  }
  return uniqueEntities;
}

void Grid::selfExpand(const Physic::Polygon& rect) {
  auto rectReach = this->rectReach(rect);
  auto br = rectReach[2];

  br /= static_cast<float>(_squareSize);
  if (br.x >= _width) {
    _width = br.x + 1;
    for (auto& lines : _grid) {
      lines.resize(_width);
    }
  }
  if (br.y >= _height) {
    size_t y = _height;
    _height = br.y + 1;
    _grid.resize(_height);
    for (; y < _height; ++y)
      _grid[y].resize(_width);
  }
}

Physic::Polygon Grid::rectReach(const Physic::Polygon& rect) const {
  const auto& vertices = rect.vertices();
  sf::Vector2f min = rect[0];
  sf::Vector2f max = rect[1];

  for (size_t i = 2; i < vertices.size(); ++i) {
    const auto& v = vertices[i];

    min.x = (v.x < min.x ? v.x : min.x);
    min.y = (v.y < min.y ? v.y : min.y);
    max.x = (v.x > max.x ? v.x : max.x);
    max.y = (v.y > max.y ? v.y : max.y);
  }
  float width = max.x - min.x;
  float height = max.y - min.y;

  return Physic::Polygon({
    sf::Vector2f(min.x, min.y),                  //
    sf::Vector2f(min.x, min.y + height),         //
    sf::Vector2f(min.x + width, min.y + height), //
    sf::Vector2f(min.x + width, min.y),          //
  });
}

Grid::Coordinate Grid::cellIndex(const sf::Vector2f& point) const {
  int x = static_cast<int>(point.x) / _squareSize;
  int y = static_cast<int>(point.y) / _squareSize;

  return {
    std::min(std::max(static_cast<size_t>(x), static_cast<size_t>(0)), _width - 1),
    std::min(std::max(static_cast<size_t>(y), static_cast<size_t>(0)), _height - 1),
  };
}

std::vector<Grid::Coordinate> Grid::overlappedCells(const Physic::Polygon& rect) const {
  std::vector<Coordinate> coordinates;
  auto tlCoordinate = this->cellIndex(rect[0]);
  auto blCoordinate = this->cellIndex(rect[1]);
  auto brCoordinate = this->cellIndex(rect[2]);

  for (size_t y = tlCoordinate.y; y <= blCoordinate.y; ++y) {
    for (size_t x = blCoordinate.x; x <= brCoordinate.x; ++x) {
      coordinates.emplace_back(x, y);
    }
  }

  return coordinates;
}

} /* namespace World */
} /* namespace GameCore */
