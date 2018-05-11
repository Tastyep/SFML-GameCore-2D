#include "world/contact/detail/ContactResolver.hpp"

namespace World {
namespace Contact {
namespace Detail {

void resolveContact(Entity::Entity* a, Entity::Entity* b, playrho::Contact& contact, const Handler& contactHandler) {
  auto* firstEntity = a->id() > b->id() ? a : b;
  auto* secondEntity = firstEntity == a ? b : a;
  const auto id = firstEntity->id();

  SWITCH_generate(id, Detail::resolveSecond);
}

} /* namespace Detail */
} /* namespace Contact */
} /* namespace World */
