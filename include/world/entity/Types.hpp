#ifndef GAME_CORE_WORLD_ENTITY_TYPES_HPP
#define GAME_CORE_WORLD_ENTITY_TYPES_HPP

#include <type_traits>

#include <boost/hana/first.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/size.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>

#include "world/entity/Ball.hpp"
#include "world/entity/EntityId.hpp"
#include "world/entity/Player.hpp"
#include "world/entity/Wall.hpp"

#include "util/EnumCast.hpp"

namespace hana = boost::hana;

namespace World {
namespace Entity {

#define MAKE_ENTITY_PAIR(Identifier, Type) hana::make_pair(hana::int_c<enum_cast(Identifier)>, hana::type_c<Type>)

#define GAME_CORE_ENTITY_COUNT 3
constexpr auto entityIdentifierMap =                 //
  hana::make_tuple(MAKE_ENTITY_PAIR(Id::Wall, Wall), //
                   MAKE_ENTITY_PAIR(Id::Ball, Ball), //
                   MAKE_ENTITY_PAIR(Id::Player, Player));

static_assert(decltype(hana::size(entityIdentifierMap))::value == GAME_CORE_ENTITY_COUNT,
              "Map size must be equal to the entity count.");

template <size_t i>
constexpr auto
  id = static_cast<Id>(std::decay<decltype(hana::first(entityIdentifierMap[hana::int_c<i>]))>::type::value);

template <size_t i>
using Type = typename std::decay<decltype(hana::second(entityIdentifierMap[hana::int_c<i>]))>::type::type;

} /* namespace Entity */
} /* namespace World */

#endif
