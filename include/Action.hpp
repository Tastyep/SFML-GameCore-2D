#ifndef GAME_CORE_ACTIONS_HPP
#define GAME_CORE_ACTIONS_HPP

#include <iostream>

enum class Action {
  ESCAPE,
  USE,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  JUMP,
};

inline std::ostream& operator<<(std::ostream& os, Action action) {
  os << static_cast<std::underlying_type<Action>::type>(action);
  return os;
}

#endif
