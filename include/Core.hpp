#ifndef GAME_CORE_HPP
#define GAME_CORE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Action.hpp"

#include "configParser/Parser.hpp"
#include "input/Manager.hpp"
#include "ressource/Manager.hpp"
#include "ressource/TileManager.hpp"

namespace GameCore {

class Core {
 private:
  const std::string kAssetDir = "../assets/";

 public:
  Core();

  void run();

 private:
  void createWindow();
  void registerParserModules();
  bool loadRessources();
  void runGameLoop();
  void shutdown();

  void parseConfigFile(const std::string& file);

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
  Ressource::Manager<sf::Texture> _textureManager;
  std::shared_ptr<Ressource::TileManager> _tileManager;

  sf::RenderWindow _window;
};

} /* namespace GameCore */

#endif
