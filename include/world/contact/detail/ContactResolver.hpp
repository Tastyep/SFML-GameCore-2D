#ifndef GAME_CORE_WORLD_CONTACT_DETAIL_CONTACT_RESOLVER_HPP
#define GAME_CORE_WORLD_CONTACT_DETAIL_CONTACT_RESOLVER_HPP

#include <boost/preprocessor/repetition/repeat.hpp>

#include "world/contact/detail/ContactHandler.hpp"
#include "world/entity/Types.hpp"

namespace GameCore {
namespace World {
namespace Contact {
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
void resolved(T1* a, T2* b, const Handler& contactHandler) {
  contactHandler.handle(*a, *b);
}

template <typename T>
void resolveSecond(T* a, Entity::Entity* b, const Handler& contactHandler) {
  auto* firstEntity = b;
  auto* secondEntity = a;
  const auto id = firstEntity->id();

  SWITCH_generate(id, resolved);
}

void resolveContact(Entity::Entity* a, Entity::Entity* b, const Handler& contactHandler);

} /* namespace Detail */
} /* namespace Contact */
} /* namespace World */
} /* namespace GameCore */

#endif
