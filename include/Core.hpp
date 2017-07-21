#ifndef GAME_CORE_HPP
#define GAME_CORE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "configParser/Parser.hpp"

namespace GameCore {

class Core {
 public:
  void run();

 private:
  void registerParserModules();

 private:
  ConfigParser::Parser _configParser;
};

} /* namespace GameCore */

#endif
