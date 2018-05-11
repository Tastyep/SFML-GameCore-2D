#ifndef GAME_CORE_CONFIG_PARSER_DETAIL_BIND_MODULE_HPP
#define GAME_CORE_CONFIG_PARSER_DETAIL_BIND_MODULE_HPP

#include "configParser/ParsingModule.hpp"

#include <unordered_map>
#include <utility>

namespace ConfigParser {
namespace Detail {

template <typename Key, typename Action>
class BindModule : public ParsingModule, public std::enable_shared_from_this<BindModule<Key, Action>> {
 private:
  const std::string _key{ "bind" };

 public:
  void setUp() override {
    _bindMapping.clear();
  }

  bool parse(const std::vector<std::string>& tokens, size_t lineCount) override {
    if (tokens.size() != 3) {
      std::cout << "Line " << lineCount << ": invalid format, should be \"bind key action\"" << std::endl;
      return false;
    }

    auto keyIt = _keyMapping.find(tokens[1]);
    if (keyIt == _keyMapping.end()) {
      std::cout << "Line " << lineCount << ": unknown key \"" << tokens[1] << "\"" << std::endl;
      return false;
    }

    auto actionIt = _actionMapping.find(tokens[2]);
    if (actionIt == _actionMapping.end()) {
      std::cout << "Line " << lineCount << ": unknown action \"" << tokens[2] << "\"" << std::endl;
      return false;
    }

    _bindMapping[keyIt->second] = actionIt->second;

    return true;
  }

  std::shared_ptr<ParsingModule> shareState() override {
    return this->shared_from_this();
  }

  const std::string& key() const override {
    return _key;
  }

 public:
  void configureKeys(std::unordered_map<std::string, Key> keyMapping) {
    _keyMapping = std::move(keyMapping);
  }

  void configureActions(std::unordered_map<std::string, Action> actionMapping) {
    _actionMapping = std::move(actionMapping);
  }

  const std::unordered_map<Key, Action> mapping() const {
    return _bindMapping;
  }

 private:
  std::unordered_map<std::string, Key> _keyMapping;
  std::unordered_map<std::string, Action> _actionMapping;
  std::unordered_map<Key, Action> _bindMapping;
};

} /* namespace Detail */
} /* namespace ConfigParser */

#endif
