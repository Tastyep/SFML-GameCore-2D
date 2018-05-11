#ifndef GAME_CORE_INPUT_ACTION_HANDLER_HPP
#define GAME_CORE_INPUT_ACTION_HANDLER_HPP

namespace Input {

template <typename Action>
class ActionHandler {
 public:
  virtual void handle(Action action) = 0;
};

} /* namespace Input */

#endif
