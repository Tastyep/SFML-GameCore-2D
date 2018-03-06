#ifndef GAME_CORE_HITBOX_DETAIL_COORDINATE_TRANSFORMER_HPP
#define GAME_CORE_HITBOX_DETAIL_COORDINATE_TRANSFORMER_HPP

#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameCore {
namespace Hitbox {
namespace Detail {

void toCarthesian(const sf::Sprite& sprite, std::vector<sf::Vector2i>& contour);

} /* namespace Detail */
} /* namespace Hitbox */
} /* namespace GameCore */

#endif
