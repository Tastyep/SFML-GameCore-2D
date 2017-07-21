#ifndef GAME_CORE_HPP
#define GAME_CORE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "Action.hpp"

#include "configParser/Parser.hpp"
#include "input/Manager.hpp"

namespace GameCore {

class Core {
 public:
  void run();

 private:
  void createWindow();
  void registerParserModules();
  void initInputModule();
  void runGameLoop();
  void shutdown();

 private:
  struct ShutdownModule : public Input::ActionHandler<Action> {
    ShutdownModule(Core* core)
      : _core(core) {}

    void handle(Action) {
      _core->shutdown();
    }

   private:
    Core* _core;
  };

 private:
  ConfigParser::Parser _configParser;
  Input::Manager<Action> _inputManager;
  sf::RenderWindow _window;
};

} /* namespace GameCore */

#endif
