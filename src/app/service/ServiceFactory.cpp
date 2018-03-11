#include "app/service/ServiceFactory.hpp"

#include <utility>

#include "app/command/CommandDispatcher.hpp"
#include "app/service/detail/EntityService.hpp"

#include "world/Core.hpp"

namespace GameCore {
namespace App {
namespace Service {

Factory::Factory(std::shared_ptr<Command::Dispatcher> commandDispatcher)
  : _commandDispatcher(std::move(commandDispatcher)) {}

void Factory::registerAll(std::shared_ptr<World::Core> world) const {
  this->makeEntityService(std::move(world));
}

void Factory::makeEntityService(std::shared_ptr<World::Core> world) const {
  Detail::makeRegistered<Detail::EntityService>(*_commandDispatcher, std::move(world));
}

} /* namespace Service */
} /* namespace App */
} /* namespace GameCore */
