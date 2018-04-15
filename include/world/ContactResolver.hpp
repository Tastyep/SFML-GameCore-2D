#ifndef GAME_CORE_CONTACT_RESOLVER_HPP
#define GAME_CORE_CONTACT_RESOLVER_HPP

#include <boost/preprocessor/repetition/repeat.hpp>

#include "world/ContactHandler.hpp"
#include "world/entity/Types.hpp"

namespace GameCore {
namespace World {
namespace Detail {

// clang-format off
#define CASE_generate(z, n, dispatcher) \
  case Entity::id<n>: \
    dispatcher(static_cast<Entity::Type<n>*>(firstEntity), secondEntity, contactHandler); \
    break;
// clang-format on

#define SWITCH_generate(id, dispatcher) \
  switch (id) { BOOST_PP_REPEAT(GAME_CORE_ENTITY_COUNT, CASE_generate, dispatcher) }

template <typename T1, typename T2>
void resolved(T1* a, T2* b, const ContactHandler& contactHandler) {
  contactHandler.handle(*a, *b);
}

template <typename T>
void resolveSecond(T* a, Entity::Entity* b, const ContactHandler& contactHandler) {
  auto* firstEntity = b;
  auto* secondEntity = a;
  const auto id = firstEntity->id();

  SWITCH_generate(id, resolved);
}

} /* namespace Detail */

void resolveContact(Entity::Entity* a, Entity::Entity* b, const ContactHandler& contactHandler);

} /* namespace World */
} /* namespace GameCore */

#endif
