#include "app/service/detail/EntityService.hpp"

#include <iostream>
#include <utility>

namespace GameCore {
namespace App {
namespace Service {
namespace Detail {

EntityService::EntityService(std::shared_ptr<World::Core> world)
  : _world(std::move(world)) {}

void EntityService::handle(const Command::AddEntity& cmd) const {
  std::cout << "handle AddEntity" << std::endl;
  _world->addEntity(cmd.entityId(), cmd.position(), cmd.velocity());
}

} /* namespace Detail */
} /* namespace Service */
} /* namespace App */
} /* namespace GameCore */