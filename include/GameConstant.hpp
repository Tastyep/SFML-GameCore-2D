#ifndef GAME_CORE_GAME_CONSTANT_HPP
#define GAME_CORE_GAME_CONSTANT_HPP

#include <chrono>
#include <string>

namespace GameCore {

const std::string kAssetDir = "../assets/";
const std::string kMapDir = "../maps/";
const std::string kConfigDir = "../config/";

const int kMapNumberLength = 2;
const int kFrameRate = 25;
const auto kTimeStepDuration = std::chrono::milliseconds(1000) / kFrameRate;
const float kTimeStep = 1.0f / static_cast<float>(kFrameRate);

const int kTileSize = 32;
const float kWorldScale = kTileSize / 2.f; // Since a player fits in a tile I want him to be 2 meters high max.

} /* namespace GameCore */

#endif
