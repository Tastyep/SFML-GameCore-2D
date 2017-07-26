#ifndef GAME_CORE_CORE_HPP
#define GAME_CORE_CORE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Action.hpp"
#include "Tile.hpp"

#include "configParser/Parser.hpp"
#include "hitbox/Manager.hpp"
#include "input/Manager.hpp"
#include "ressource/Manager.hpp"
#include "ressource/TileManager.hpp"
#include "world/Core.hpp"

namespace GameCore {

class Core {
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
  std::shared_ptr<Hitbox::Manager<Tile>> _hitboxManager;
  std::unique_ptr<World::Core> _world;

  sf::RenderWindow _window;
};

} /* namespace GameCore */

#endif
