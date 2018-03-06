#ifndef GAME_CORE_GAME_CONSTANT_HPP
#define GAME_CORE_GAME_CONSTANT_HPP

#include <chrono>
#include <string>

#include <SFML/System/Vector2.hpp>

namespace GameCore {

const std::string kAssetDir = "../assets/";
const std::string kMapDir = "../maps/";
const std::string kConfigDir = "../config/";

const int kMapNumberLength = 2;
const int kFrameRate = 30;
const auto kTimeStepDuration = std::chrono::milliseconds(1000) / kFrameRate;
const float kTimeStep = 1.0f / static_cast<float>(kFrameRate);

const int kTileSize = 32;
const sf::Vector2f kSpriteOrigin{ kTileSize / 2, kTileSize / 2 };

} /* namespace GameCore */

#endif
