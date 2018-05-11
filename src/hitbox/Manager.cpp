#include "hitbox/Manager.hpp"

namespace Hitbox {

void Manager::load(size_t id, const sf::Sprite& sprite, size_t accuracy) {
  _manager.load(id, sprite, accuracy, true);
  auto polygons = _manager.get(id).body();

  this->translatePolygons(polygons, static_cast<sf::Vector2i>(kSpriteOrigin));
  this->makeBody(id, polygons);
}

const std::vector<playrho::PolygonShape>& Manager::body(size_t id) const {
  auto found = _hitboxes.find(id);
  assert(found != _hitboxes.end());

  return found->second;
}

// Private member functions

void Manager::makeBody(size_t id, const std::vector<Polygon>& polygons) {
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

void Manager::translatePolygons(std::vector<Polygon>& polygons, const sf::Vector2i& center) const {
  for (auto& polygon : polygons) {
    for (auto& v : polygon) {
      v -= center;
    }
  }
}

} /* namespace Hitbox */
