#include "world/ContactResolver.hpp"

namespace GameCore {
namespace World {

void resolveContact(Entity::Entity* a, Entity::Entity* b, const ContactHandler& contactHandler) {
  auto* firstEntity = a->id() > b->id() ? a : b;
  auto* secondEntity = firstEntity == a ? b : a;
  const auto id = firstEntity->id();

  SWITCH_generate(id, Detail::resolveSecond);
}

} /* namespace World */
} /* namespace GameCore */
