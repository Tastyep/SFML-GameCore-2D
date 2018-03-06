#include "hitbox/detail/CoordinateTransformer.hpp"

namespace GameCore {
namespace Hitbox {
namespace Detail {

void toCarthesian(const sf::Sprite& sprite, std::vector<sf::Vector2i>& contour) {
  const auto bound = sprite.getLocalBounds();

  std::transform(contour.begin(), contour.end(), contour.begin(), [&bound](auto& v) -> sf::Vector2i {
    return { v.x, -1 * (v.y - static_cast<int>(bound.height)) };
  });
}

} /* namespace Detail */
} /* namespace Hitbox */
} /* namespace GameCore */
