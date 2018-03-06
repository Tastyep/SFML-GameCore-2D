#ifndef GAME_CORE_INPUT_DISPATCHER_HPP
#define GAME_CORE_INPUT_DISPATCHER_HPP

#include <initializer_list>
#include <memory>
#include <vector>

#include "input/ActionHandler.hpp"

namespace GameCore {
namespace Input {

template <typename Action>
class Dispatcher {
 public:
  virtual ~Dispatcher() = default;

  // clang-format off
  virtual void registerHandler(std::initializer_list<Action> actions,
                               std::shared_ptr<ActionHandler<Action>> handler) = 0;
  // clang-format on
  virtual void registerHandler(Action action, std::shared_ptr<ActionHandler<Action>> handler) = 0;
  virtual void dispatch(Action action) const = 0;
};

} /* namespace Input */
} /* namespace GameCore */

#endif
