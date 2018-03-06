#ifndef GAME_CORE_WORLD_CONSTANT_HPP
#define GAME_CORE_WORLD_CONSTANT_HPP

#include <cmath>

#include "PlayRho/Common/Vector2D.hpp"

#include "GameConstant.hpp"

namespace GameCore {
namespace World {

const float kPixelScale = static_cast<float>(kTileSize) / 2.f;
const float kWorldScale = 2.f / static_cast<float>(kTileSize);

const float kGravity = 0; // 9.81f;
const int kVelocityIt = 6;
const int kPositionIt = 2;

const playrho::Length2D kBodyCenter{ 1, 1 };

const float pi = std::acos(-1);
const float rad = pi / 180.f;
const float deg = 180.f / pi;

} /* namespace World */
} /* namespace GameCore */

#endif
