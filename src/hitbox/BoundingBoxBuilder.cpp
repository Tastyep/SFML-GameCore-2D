#include "hitbox/BoundingBoxBuilder.hpp"

#include <algorithm>

namespace GameCore {
namespace Hitbox {

sf::FloatRect BoundingBoxBuilder::make(const std::vector<sf::Vector2f>& polygon) const {
  sf::Vector2f tl = polygon.front(), br = polygon.front();

  for (const auto& v : polygon) {
    tl.x = std::min(tl.x, v.x);
    tl.y = std::min(tl.y, v.y);
    br.x = std::max(br.x, v.x);
    br.y = std::max(br.y, v.y);
  }

  return sf::FloatRect{ tl.x, tl.y, br.x - tl.x, br.y - tl.y };
}

} /* namespace Hitbox */
} /* namespace GameCore */
