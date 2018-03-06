#ifndef GAME_CORE_INPUT_DETAIL_KEY_STATE_RECORDER_HPP
#define GAME_CORE_INPUT_DETAIL_KEY_STATE_RECORDER_HPP

#include <vector>

#include <SFML/Window/Keyboard.hpp>

namespace GameCore {
namespace Input {
namespace Detail {

class KeyStateRecorder {
 public:
  void observeKey(sf::Keyboard::Key key);
  bool forgetKey(sf::Keyboard::Key key);
  void checkKeys();
  std::vector<sf::Keyboard::Key> pressedKeys() const;

 private:
  struct KeyState {
    explicit KeyState(sf::Keyboard::Key code, bool state = false)
      : code(code)
      , state(state) {}

    sf::Keyboard::Key code;
    bool state;
  };

 private:
  std::vector<KeyState> _keys;
};

} /* namespace Detail */
} /* namespace Input */
} /* namespace GameCore */

#endif
