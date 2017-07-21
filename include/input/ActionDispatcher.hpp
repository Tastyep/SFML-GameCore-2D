#ifndef GAME_CORE_INPUT_ACTION_DISPATCHER_HPP
#define GAME_CORE_INPUT_ACTION_DISPATCHER_HPP

#include <memory>
#include <unordered_map>
#include <vector>

#include "input/ActionHandler.hpp"

namespace GameCore {
namespace Input {

template <typename Action>
class Dispatcher {
 public:
  Dispatcher() = default;

  void registerHandler(Action action, std::shared_ptr<ActionHandler<Action>> handler) {
    _handlers[action].emplace_back(std::move(handler));
  }

  void dispatch(Action action) const {
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

} /* namespace Input */
} /* namespace GameCore */

#endif
