#include "world/Core.hpp"

#include "PlayRho/Common/Math.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include "world/WorldConstant.hpp"

#include "world/entity/EntityId.hpp"

namespace GameCore {
namespace World {

Core::Core(std::unique_ptr<Entity::Factory> entityFactory, const sf::FloatRect& viewRect)
  : _entityFactory(std::move(entityFactory))
  , _camera(viewRect) {
  _world = std::make_shared<playrho::World>(playrho::WorldDef{}.UseGravity(playrho::LinearAcceleration2D(0, 0)));
  _entityFactory->setWorld(_world);
  _world->SetContactListener(&_contactListener);
  _stepConf.SetTime(kTimeStep);
}

void Core::update() {
  for (auto& entity : _entities) {
    entity->update();
  }

  _world->Step(_stepConf);
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
      auto id = static_cast<Entity::Id>(std::stoi(number));
      auto screenPos = sf::Vector2f(static_cast<float>(x), static_cast<float>(y)) * static_cast<float>(kTileSize);
      auto sp = playrho::Length2D(screenPos.x, screenPos.y);

      auto entity = _entityFactory->make(id, sp);
      if (!entity) {
        std::cerr << "Error | line: " << y << " | c: " << x << " | Invalid tild id: " << enum_cast(id) << "."
                  << std::endl;
        _entities.clear();
        return false;
      }

      _entities.push_back(std::move(entity));
    }
  }
  return true;
}

} /* namespace World */
} /* namespace GameCore */
