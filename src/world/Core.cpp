#include "world/Core.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include "world/WorldConstant.hpp"

namespace GameCore {
namespace World {

Core::Core(std::unique_ptr<Entity::Factory> entityFactory, const sf::FloatRect& viewRect)
  : _entityFactory(std::move(entityFactory))
  , _camera(viewRect) {
  _world = std::make_shared<b2World>(b2Vec2(0.f, -kGravity));
  _entityFactory->setWorld(_world);
}

void Core::update() {
  _world->Step(kTimeStep, kVelocityIt, kPositionIt);

  for (auto& entity : _entities) {
    entity->update();
  }
}

void Core::draw(sf::RenderTarget& target, sf::RenderStates) const {
  for (const auto& entity : _entities) {
    target.draw(*entity);
  }
}

bool Core::loadMap(const std::string& filePath) {
  std::ifstream fileStream(filePath, std::ios::binary);

  if (!fileStream.is_open()) {
    std::cout << "Error: Failed to open " << filePath << std::endl;
    return false;
  }

  std::string line;
  for (size_t y = 0; std::getline(fileStream, line); ++y) {
    size_t lineSize = line.size();
    if (lineSize % kMapNumberLength) {
      std::cerr << "Error | line: " << y << " | Invalid format." << std::endl;
      return false;
    }
    for (size_t x = 0, i = 0; i < lineSize; i += kMapNumberLength, ++x) {
      if (line[i] == ' ' || line[i] == '\t') {
        continue;
      }
      std::string number(line, i, kMapNumberLength);
      Tile id = static_cast<Tile>(std::stoi(number));
      std::shared_ptr<Entity::Entity> entity;
      auto screenPos = sf::Vector2f(static_cast<float>(x), static_cast<float>(y)) * static_cast<float>(kTileSize);

      // clang-format off
      switch (id) {
      case Tile::PLAYER:
        entity = _entityFactory->create<Entity::Player>(screenPos);
        break;
      case Tile::WALL:
        entity = _entityFactory->create<Entity::Wall>(screenPos);
        break;
      case Tile::BALL:
        entity = _entityFactory->create<Entity::Ball>(screenPos);
        break;
      default:
        std::cerr << "Error | line: " << y << " | c: " << x << " | Invalid tild id: " << enum_cast(id) << "."
                  << std::endl;
        _entities.clear();
        return false;
      }
      // clang-format on

      _entities.push_back(std::move(entity));
    }
  }
  return true;
}

} /* namespace World */
} /* namespace GameCore */
