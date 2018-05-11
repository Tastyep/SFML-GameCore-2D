#ifndef GAME_CORE_CONFIG_PARSER_PARSER_HPP
#define GAME_CORE_CONFIG_PARSER_PARSER_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include "configParser/ParsingModule.hpp"

namespace ConfigParser {

class Parser {
 public:
  void registerModule(std::shared_ptr<ParsingModule> module);
  std::shared_ptr<ParsingModule> module(const std::string& name);

  bool parse(const std::string& filePath);

 private:
  std::unordered_map<std::string, std::shared_ptr<ParsingModule>> _modules;
};

} /* namespace ConfigParser */

#endif
