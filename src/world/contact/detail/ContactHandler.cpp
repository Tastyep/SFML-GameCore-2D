#include "world/contact/detail/ContactHandler.hpp"

#include "world/entity/Ball.hpp"
#include "world/entity/Player.hpp"
#include "world/entity/Wall.hpp"

#include "util/EnumCast.hpp"

namespace GameCore {
namespace World {
namespace Contact {
namespace Detail {

void Handler::handle(Entity::Entity& a, Entity::Entity& b, playrho::Contact& contact) const {
  std::cout << "missing contact handler for [" << enum_cast(a.id()) << ", " << enum_cast(b.id()) << "]" << std::endl;
}

void Handler::handle(Entity::Wall& wall, Entity::Ball& ball, playrho::Contact& contact) const {
  const auto& manifold = contact.GetManifold();
  const auto normal = manifold.GetLocalNormal();

  ball.bounce(normal);
}

void Handler::handle(Entity::Wall& wall, Entity::Player& player, playrho::Contact& contact) const {}

void Handler::handle(Entity::Ball& a, Entity::Ball& b, playrho::Contact& contact) const {}

void Handler::handle(Entity::Ball& ball, Entity::Player& player, playrho::Contact& contact) const {}

void Handler::handle(Entity::Player& a, Entity::Player& b, playrho::Contact& contact) const {}

} /* namespace Detail */
} /* namespace Contact */
} /* namespace World */
} /* namespace GameCore */
