#ifndef GAME_CORE_CONFIG_PARSER_PARSING_MODULE_HPP
#define GAME_CORE_CONFIG_PARSER_PARSING_MODULE_HPP

#include <memory>
#include <string>
#include <vector>

#include "configParser/ParsingModule.hpp"

namespace ConfigParser {

class ParsingModule {
 public:
  virtual ~ParsingModule() = default;

  virtual void setUp() = 0;
  virtual bool parse(const std::vector<std::string>& tokens, size_t lineCount) = 0;
  virtual std::shared_ptr<ParsingModule> shareState() = 0;
  virtual const std::string& key() const = 0;
};

} /* namespace ConfigParser */

#endif
