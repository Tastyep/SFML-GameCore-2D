#ifndef GAME_CORE_INPUT_DETAIL_KEY_MAPPER_HPP
#define GAME_CORE_INPUT_DETAIL_KEY_MAPPER_HPP

#include <cassert>
#include <unordered_map>

#include <SFML/Window/Keyboard.hpp>

namespace Input {
namespace Detail {

template <typename Action>
class KeyMapper {
 public:
  void map(sf::Keyboard::Key key, Action a) {
    _keyMapper[key] = a;
  }

  void unmap(sf::Keyboard::Key key) {
    _keyMapper.erase(key);
  }

  Action operator[](sf::Keyboard::Key key) const {
    auto it = _keyMapper.find(key);
    assert(it != _keyMapper.end());

    return it->second;
  }

 private:
  std::unordered_map<sf::Keyboard::Key, Action> _keyMapper;
};

} /* namespace Detail */
} /* namespace Input */

#endif
