#ifndef GAME_CORE_APP_COMMAND_COMMAND_DISPATCHER_HPP
#define GAME_CORE_APP_COMMAND_COMMAND_DISPATCHER_HPP

#include <cassert>
#include <functional>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>

#include "TaskManager.hpp"
#include "app/command/CommandHandler.hpp"

namespace GameCore {
namespace App {
namespace Command {

class Dispatcher {
 public:
  Dispatcher(std::shared_ptr<TaskManager> taskManager)
    : _taskManager(std::move(taskManager)) {}

  template <typename Command>
  void registerHandler(std::shared_ptr<Handler<Command>> handler) {
    assert(handler);
    _handlers.emplace(this->index<Command>(), std::move(handler));
  }

  template <typename Command>
  void dispatch(Command cmd) const {
    BaseHandler* handler;

    auto it = _handlers.find(this->index<Command>());
    handler = it != _handlers.end() ? it->second.get() : nullptr;

    if (handler) {
      _taskManager->add([handler, cmd = std::move(cmd)] {
        const auto& h = static_cast<const Handler<Command>&>(*handler);
        h.handle(cmd);
      });
    }
  }

 private:
  using HandlerTypeMap = std::unordered_map<std::type_index, std::shared_ptr<BaseHandler>>;

 private:
  //! Get the type index of a command type.
  template <typename Command>
  std::type_index index() const {
    return std::type_index(typeid(Command));
  }

 private:
  HandlerTypeMap _handlers;
  std::shared_ptr<TaskManager> _taskManager;
};

} /* namespace Command */
} /* namespace App */
} /* namespace GameCore */

#endif
