#ifndef GAME_CORE_GAME_CONSTANT_HPP
#define GAME_CORE_GAME_CONSTANT_HPP

#include <chrono>
#include <string>

namespace GameCore {

const std::string kAssetDir = "../assets/";
const std::string kMapDir = "../maps/";
const std::string kConfigDir = "../config/";

const int kTileSize = 32;
const int kMapNumberLength = 2;
const int kFrameRate = 25;
const auto kTimeStep = std::chrono::milliseconds(1000) / kFrameRate;

} /* namespace GameCore */

#endif
