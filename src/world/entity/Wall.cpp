#include "world/entity/Wall.hpp"

namespace World {
namespace Entity {

Wall::Wall(playrho::Body* body, const sf::Sprite& sprite, const App::Command::Dispatcher& commandDispatcher)
  : Entity(std::move(body), sprite, commandDispatcher) {}

void Wall::update() {}

Id Wall::id() const {
  return Id::Wall;
}

} /* namespace Entity */
} /* namespace World */
