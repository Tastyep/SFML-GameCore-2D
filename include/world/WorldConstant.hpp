#ifndef GAME_CORE_WORLD_CONSTANT_HPP
#define GAME_CORE_WORLD_CONSTANT_HPP

#include "GameConstant.hpp"

namespace GameCore {
namespace World {

const sf::Vector2f kEntityOrigin = { static_cast<float>(GameCore::kTileSize) / 2.f,
                                     static_cast<float>(GameCore::kTileSize) / 2.f };

const float kGravity = 9.81;

} /* namespace World */
} /* namespace GameCore */

#endif
