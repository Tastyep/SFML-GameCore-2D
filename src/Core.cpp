#include "Core.hpp"

#include <chrono>
#include <cstddef>
#include <memory>
#include <utility>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "configParser/BindModule.hpp"
#include "input/Manager.hpp"
#include "util/EnumCast.hpp"

using namespace std::literals::chrono_literals;

namespace GameCore {

Core::Core()
  : _tileManager(std::make_shared<Ressource::TileManager>())
  , _hitboxManager(std::make_shared<Hitbox::Manager<Tile>>()) {}

void Core::run() {
  this->createWindow();
  this->registerParserModules();
  this->parseConfigFile("./Game.cfg");
  if (!this->loadRessources()) {
    return;
  }

  _inputManager.dispatcher()->registerHandler(Action::ESCAPE, std::make_shared<ShutdownModule>(this));

  this->runGameLoop();
}

void Core::runGameLoop() {
  const size_t ticksPerSecond = 30;
  const size_t maxFrameSkip = 5;
  const auto skipTicks = 1000ms / ticksPerSecond;

  sf::Event event;
  auto nextGameTick = std::chrono::steady_clock::now();
  while (_window.isOpen()) {
    while (_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        this->shutdown();
      }
    }

    for (size_t loopCount = 0; std::chrono::steady_clock::now() > nextGameTick && loopCount < maxFrameSkip;
         ++loopCount) {
      // this->updatePhysic();
      nextGameTick += skipTicks;
      ++loopCount;
    }

    // Checks the key pressed and dispatches the associated actions.
    _inputManager.run();

    _window.clear();
    _window.display();
  }
}

void Core::shutdown() {
  _window.close();
}

void Core::createWindow() {
  _window.create(sf::VideoMode(1000, 1000), "GameCore");
  _window.setFramerateLimit(60);
}

void Core::parseConfigFile(const std::string& file) {
  using Key = sf::Keyboard::Key;
  _configParser.parse(file);

  auto bindModule = std::static_pointer_cast<ConfigParser::BindModule<Key, Action>>(_configParser.module("bind"));
  auto bindMapping = bindModule->mapping();

  // Bind keys on actions.
  for (const auto& mapping : bindMapping) {
    _inputManager.bind(mapping.first, mapping.second);
  }
}

bool Core::loadRessources() {
  if (!_textureManager.load("mainAsset", kAssetDir + "asset.png")) {
    return false;
  }
  const auto& mainTexture = _textureManager.get("mainAsset");
  _tileManager->parse(mainTexture, 32);

  for (auto id = enum_cast(Tile::PLAYER); id <= enum_cast(Tile::FLOOR); ++id) {
    _hitboxManager->load(static_cast<Tile>(id), _tileManager->tile(static_cast<Tile>(id)), 80);
  }
  return true;
}

void Core::registerParserModules() {
  using Key = sf::Keyboard::Key;
  auto bindModule = std::make_shared<ConfigParser::BindModule<Key, Action>>();

  bindModule->configureActions({
    { "Escape", Action::ESCAPE },
    { "Use", Action::USE },
    { "MoveUp", Action::UP },
    { "MoveDown", Action::DOWN },
    { "MoveLeft", Action::LEFT },
    { "MoveRight", Action::RIGHT },
    { "Jump", Action::JUMP },
  });

  bindModule->configureKeys({
    { "0", Key::Num0 },
    { "1", Key::Num1 },
    { "2", Key::Num2 },
    { "3", Key::Num3 },
    { "4", Key::Num4 },
    { "5", Key::Num5 },
    { "6", Key::Num6 },
    { "7", Key::Num7 },
    { "8", Key::Num8 },
    { "9", Key::Num9 },
    //
    { "A", Key::A },
    { "B", Key::B },
    { "C", Key::C },
    { "D", Key::D },
    { "E", Key::E },
    { "F", Key::F },
    { "G", Key::G },
    { "H", Key::H },
    { "I", Key::I },
    { "J", Key::J },
    { "K", Key::K },
    { "L", Key::L },
    { "M", Key::M },
    { "N", Key::N },
    { "O", Key::O },
    { "P", Key::P },
    { "Q", Key::Q },
    { "R", Key::R },
    { "S", Key::S },
    { "T", Key::T },
    { "U", Key::U },
    { "V", Key::V },
    { "W", Key::W },
    { "X", Key::X },
    { "Y", Key::Y },
    { "Z", Key::Z },
    //
    { "F1", Key::F1 },
    { "F2", Key::F2 },
    { "F3", Key::F3 },
    { "F4", Key::F4 },
    { "F5", Key::F5 },
    { "F6", Key::F6 },
    { "F7", Key::F7 },
    { "F8", Key::F8 },
    { "F9", Key::F9 },
    { "F10", Key::F10 },
    { "F11", Key::F11 },
    { "F12", Key::F12 },
    { "F13", Key::F13 },
    { "F14", Key::F14 },
    { "F15", Key::F15 },
    //
    { "ESCAPE", Key::Escape },
    { "L_CTRL", Key::LControl },
    { "L_SHIFT", Key::LShift },
    { "L_ALT", Key::LAlt },
    { "L_SYSTEM", Key::LSystem },
    { "R_CTRL", Key::RControl },
    { "R_SHIFT", Key::RShift },
    { "R_ALT", Key::RAlt },
    { "R_SYSTEM", Key::RSystem },
    { "MENU", Key::Menu },
    { "LBRACKET", Key::LBracket },
    { "RBRACKET", Key::RBracket },
    { "SEMICOLON", Key::SemiColon },
    { "COMMA", Key::Comma },
    { "PERIOD", Key::Period },
    { "SLASH", Key::Slash },
    { "BACKSLASH", Key::BackSlash },
    { "TILDE", Key::Tilde },
    { "EQUAL", Key::Equal },
    { "DASH", Key::Dash },
    { "SPACE", Key::Space },
    { "ENTER", Key::Return },
    { "BACKSPACE", Key::BackSpace },
    { "TAB", Key::Tab },
    { "PGUP", Key::PageUp },
    { "PGDN", Key::PageDown },
    { "HOME", Key::Home },
    { "INS", Key::Insert },
    { "DEL", Key::Delete },
    { "PLUS", Key::Add },
    { "MINUS", Key::Subtract },
    { "MULT", Key::Multiply },
    { "DIV", Key::Divide },
    //
    { "UPARROW", Key::Up },
    { "DOWNARROW", Key::Down },
    { "LEFTARROW", Key::Left },
    { "RIGHTARROW", Key::Right },
  });

  _configParser.registerModule(std::move(bindModule));
}

} /* namespace GameCore */
