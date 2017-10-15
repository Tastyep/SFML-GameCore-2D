#ifndef GAME_CORE_WORLD_CONSTANT_HPP
#define GAME_CORE_WORLD_CONSTANT_HPP

#include "GameConstant.hpp"

namespace GameCore {
namespace World {

const sf::Vector2f kEntityOrigin = { static_cast<float>(GameCore::kTileSize) / 2.f,
                                     static_cast<float>(GameCore::kTileSize) / 2.f };

const float kGravity = 0; // 9.81f;
const int kVelocityIt = 6;
const int kPositionIt = 2;

} /* namespace World */
} /* namespace GameCore */

#endif
