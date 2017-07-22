#ifndef GANE_CORE_UTIL_ENUM_CAST_HPP
#define GANE_CORE_UTIL_ENUM_CAST_HPP

#include <type_traits>

template <typename Enum, typename = std::enable_if_t<std::is_enum<Enum>::value>>
constexpr std::underlying_type_t<Enum> enum_cast(Enum e) {
  return static_cast<std::underlying_type_t<Enum>>(e);
}

#endif
