#ifndef GAME_CORE_HITBOX_BOUNDING_BOX_BUILDER_HPP
#define GAME_CORE_HITBOX_BOUNDING_BOX_BUILDER_HPP

#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameCore {
namespace Hitbox {

class BoundingBoxBuilder {
 public:
  sf::FloatRect make(const std::vector<sf::Vector2f>& polygon) const;
};

} /* namespace Hitbox */
} /* namespace GameCore */

#endif
