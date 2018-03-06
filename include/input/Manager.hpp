#ifndef GAME_CORE_INPUT_MANAGER_HPP
#define GAME_CORE_INPUT_MANAGER_HPP

#include <memory>
#include <utility>

#include "input/Dispatcher.hpp"
#include "input/detail/KeyMapper.hpp"
#include "input/detail/KeyStateRecorder.hpp"

namespace GameCore {
namespace Input {

template <typename Action>
class Manager {
 public:
  explicit Manager(std::shared_ptr<Dispatcher<Action>> dispatcher)
    : _dispatcher(std::move(dispatcher)) {}

  void run() {
    _keyStateRecorder.checkKeys();
    const auto pressedKeys = _keyStateRecorder.pressedKeys();

    for (auto keyCode : pressedKeys) {
      auto action = _keyMapper[keyCode];

      _dispatcher->dispatch(action);
    }
  }

  void bind(sf::Keyboard::Key key, Action action) {
    _keyStateRecorder.observeKey(key);
    _keyMapper.map(key, action);
  }

  bool unbind(sf::Keyboard::Key key) {
    if (_keyStateRecorder.forgetKey(key)) {
      _keyMapper.unmap(key);
      return true;
    }
    return false;
  }

 public:
  std::shared_ptr<Dispatcher<Action>> dispatcher() const {
    return _dispatcher;
  }

 private:
  Detail::KeyStateRecorder _keyStateRecorder;
  Detail::KeyMapper<Action> _keyMapper;
  std::shared_ptr<Dispatcher<Action>> _dispatcher;
};
} /* namespace Input */
} /* namespace GameCore */

#endif
