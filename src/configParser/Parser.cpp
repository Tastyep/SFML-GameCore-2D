#include "configParser/Parser.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace ConfigParser {

void Parser::registerModule(std::shared_ptr<ParsingModule> module) {
  _modules.emplace(module->key(), std::move(module));
}

std::shared_ptr<ParsingModule> Parser::module(const std::string& key) {
  auto it = _modules.find(key);

  if (it != _modules.end()) {
    return it->second->shareState();
  }
  return nullptr;
}

bool Parser::parse(const std::string& filePath) {
  std::ifstream fileStream(filePath, std::ios::binary);

  if (!fileStream.is_open()) {
    std::cout << "failed to open " << filePath << std::endl;
    return false;
  }
  std::string line;

  // Init all modules.
  for (auto& module : _modules) {
    module.second->setUp();
  }

  for (size_t lineCount = 1; std::getline(fileStream, line); ++lineCount) {
    std::stringstream tokenStream(line);
    std::vector<std::string> tokens;
    std::string token;

    while (tokenStream >> token) {
      tokens.push_back(std::move(token));
    }

    if (tokens.empty()) {
      continue;
    }
    auto it = _modules.find(tokens[0]);

    // Unknown keyword.
    if (it == _modules.end()) {
      std::cout << "Line " << lineCount << ": unknown keyword " << tokens[0] << std::endl;
      return false;
    }
    // Invalid arguments.
    if (it->second->parse(tokens, lineCount) == false) {
      return false;
    }
  }
  return true;
}

} /* namespace ConfigParser */
