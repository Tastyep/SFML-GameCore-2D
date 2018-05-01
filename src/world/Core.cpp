#include "world/Core.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include "PlayRho/Dynamics/BodyDef.hpp"

#include "world/WorldConstant.hpp"

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
  std::lock_guard<std::mutex> lock(_entityMutex);
  const auto& entities = _entityManager.list();
  for (auto& entity : entities) {
    entity->update();
  }

  _world->Step(_stepConf);
}

void Core::draw(sf::RenderTarget& target, sf::RenderStates) const {
  std::lock_guard<std::mutex> lock(_entityMutex);
  const auto& entities = _entityManager.list();
  for (auto& entity : entities) {
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
      auto pos =
        playrho::Length2D(static_cast<float>(x), static_cast<float>(y)) * static_cast<float>(kTileSize) * kWorldScale;
      auto velocity = playrho::LinearVelocity2D{};

      if (!this->addEntity(id, pos, velocity)) {
        std::cerr << "Error | line: " << y << " | c: " << x << " | Invalid tild id: " << enum_cast(id) << "."
                  << std::endl;

        _entityManager.clear();
        return false;
      }
    }
  }
  return true;
}

bool Core::addEntity(Entity::Id entityId, playrho::Length2D position, playrho::LinearVelocity2D velocity) {
  std::lock_guard<std::mutex> lock(_entityMutex);
  auto bodyDef = playrho::BodyDef{} //
                   .UseLocation(position)
                   .UseLinearVelocity(velocity);
  auto entity = _entityFactory->make(entityId, bodyDef);

  if (!entity) {
    return false;
  }
  _entityManager.add(std::move(entity));

  return true;
}

} /* namespace World */
} /* namespace GameCore */
