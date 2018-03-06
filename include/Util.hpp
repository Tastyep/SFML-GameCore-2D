#ifndef GAME_CORE_UTIL_HPP
#define GAME_CORE_UTIL_HPP

#include <cmath>

namespace GameCore {
namespace Util {

constexpr auto toRad(float angle) {
  return angle * M_PI / 180.f;
}

constexpr auto toDeg(float angle) {
  return angle * 180.f / M_PI;
}

} /* namespace Util */
} /* namespace GameCore */

#endif
