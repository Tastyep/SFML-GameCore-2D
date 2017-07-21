#include "input/KeyStateRecorder.hpp"

#include <algorithm>

namespace GameCore {
namespace Input {

void KeyStateRecorder::observeKey(sf::Keyboard::Key keyCode) {
  if (std::find_if(_keys.begin(), _keys.end(),                                 //
                   [keyCode](const auto& key) { return key.code == keyCode; }) //
      == _keys.end()) {
    _keys.emplace_back(keyCode);
  }
}

bool KeyStateRecorder::forgetKey(sf::Keyboard::Key keyCode) {
  auto found = std::find_if(_keys.begin(), _keys.end(),                                  //
                            [keyCode](const auto& key) { return key.code == keyCode; }); //
  if (found != _keys.end()) {
    _keys.erase(found);
    return true;
  }
  return false;
}

void KeyStateRecorder::checkKeys() {
  for (auto& key : _keys) {
    key.state = sf::Keyboard::isKeyPressed(key.code);
  }
}

std::vector<sf::Keyboard::Key> KeyStateRecorder::pressedKeys() const {
  std::vector<sf::Keyboard::Key> pressedKeys;

  for (const auto& key : _keys) {
    if (key.state) {
      pressedKeys.push_back(key.code);
    }
  }
  return pressedKeys;
}

} /* namespace Input */
} /* namespace GameCore */
