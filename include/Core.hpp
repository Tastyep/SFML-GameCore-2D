#ifndef GAME_CORE_HPP
#define GAME_CORE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "configParser/Parser.hpp"

namespace GameCore {

class Core {
 public:
  void run();

 private:
  void createWindow();
  void registerParserModules();
  void runGameLoop();
  void shutdown();

 private:
  ConfigParser::Parser _configParser;
  sf::RenderWindow _window;
};

} /* namespace GameCore */

#endif
