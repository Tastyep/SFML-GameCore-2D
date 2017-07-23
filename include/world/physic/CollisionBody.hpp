#ifndef GAME_CORE_WORLD_PHYSIC_COLLISION_BODY_HPP
#define GAME_CORE_WORLD_PHYSIC_COLLISION_BODY_HPP

#include <algorithm>
#include <utility>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "world/physic/Polygon.hpp"

namespace GameCore {
namespace World {
namespace Physic {

class CollisionBody {
 public:
  using Bbox = Polygon;
  using Body = std::vector<Polygon>;

 public:
  CollisionBody(const sf::Rect<int>& bbox, const std::vector<std::vector<sf::Vector2i>>& polygons);

  void setPosition(const sf::Vector2f& position);
  void move(const sf::Vector2f& distance);

 public:
  const Bbox& boundingBox() const;
  const Body& body() const;

 private:
  Bbox _boundingBox;
  Body _body;
};

} /* namespace Physic */
} /* namespace World */
} /* namespace GameCore */

#endif
