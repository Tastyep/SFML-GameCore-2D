#ifndef GAME_CORE_APP_SERVICE_SERVICE_FACTORY_HPP
#define GAME_CORE_APP_SERVICE_SERVICE_FACTORY_HPP

#include <memory>

#include "app/command/CommandDispatcher.hpp"

namespace World {

class Core;

} /* namespace World */

namespace App {
namespace Command {

class Dispatcher;

} /* namespace Command */

namespace Service {

class Factory {
 public:
  Factory(std::shared_ptr<Command::Dispatcher> commandDispatcher);

  void registerAll(std::shared_ptr<World::Core> world) const;
  void makeEntityService(std::shared_ptr<World::Core> world) const;

 private:
  std::shared_ptr<Command::Dispatcher> _commandDispatcher;
};

} /* namespace Service */
} /* namespace App */

#endif
