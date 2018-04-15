#include "world/contact/detail/ContactHandler.hpp"

#include "world/entity/Ball.hpp"
#include "world/entity/Player.hpp"
#include "world/entity/Wall.hpp"

#include "util/EnumCast.hpp"

namespace GameCore {
namespace World {
namespace Contact {
namespace Detail {

void Handler::handle(Entity::Entity& a, Entity::Entity& b) const {
  std::cout << "missing contact handler for [" << enum_cast(a.id()) << ", " << enum_cast(b.id()) << "]" << std::endl;
}

void Handler::handle(Entity::Wall& wall, Entity::Ball& ball) const {
  std::cout << "Ball Wall contact" << std::endl;
}

void Handler::handle(Entity::Wall& wall, Entity::Player& player) const {
  std::cout << "Player Wall contact" << std::endl;
}

void Handler::handle(Entity::Ball& a, Entity::Ball& b) const {
  std::cout << "Ball Ball contact" << std::endl;
}

void Handler::handle(Entity::Ball& ball, Entity::Player& player) const {
  std::cout << "Player Ball contact" << std::endl;
}

void Handler::handle(Entity::Player& a, Entity::Player& b) const {
  std::cout << "Player Player contact" << std::endl;
}

} /* namespace Detail */
} /* namespace Contact */
} /* namespace World */
} /* namespace GameCore */
