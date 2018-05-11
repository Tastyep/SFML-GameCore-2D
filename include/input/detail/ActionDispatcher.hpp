#ifndef GAME_CORE_INPUT_ACTION_DISPATCHER_IMPL_HPP
#define GAME_CORE_INPUT_ACTION_DISPATCHER_IMPL_HPP

#include <unordered_map>

#include "input/Dispatcher.hpp"

namespace Input {
namespace Detail {

template <typename Action>
class ActionDispatcher : public Input::Dispatcher<Action> {
 public:
  void registerHandler(std::initializer_list<Action> actions, std::shared_ptr<ActionHandler<Action>> handler) override {
    for (const auto& action : actions) {
      this->registerHandler(action, handler);
    }
  }

  void registerHandler(Action action, std::shared_ptr<ActionHandler<Action>> handler) override {
    _handlers[action].emplace_back(std::move(handler));
  }

  void dispatch(Action action) const override {
    auto it = _handlers.find(action);

    if (it != _handlers.end()) {
      for (const auto& handler : it->second) {
        handler->handle(action);
      }
    }
  }

 private:
  std::unordered_map<Action, std::vector<std::shared_ptr<ActionHandler<Action>>>> _handlers;
};

} /* namespace Detail */
} /* namespace Input */

#endif
