#ifndef GAME_CORE_APP_SERVICE_DETAIL_ENTITY_SERVICE_HPP
#define GAME_CORE_APP_SERVICE_DETAIL_ENTITY_SERVICE_HPP

#include <memory>

#include "app/command/EntityCommands.hpp"
#include "app/service/detail/ServiceImpl.hpp"

#include "world/Core.hpp"

namespace App {
namespace Service {
namespace Detail {

class EntityService final : public ServiceImpl<Command::EntityCommands> {
 public:
  EntityService(std::shared_ptr<World::Core> world);

  void handle(const Command::AddEntity& cmd) const override;

 private:
  std::shared_ptr<World::Core> _world;
};

} /* namespace Detail */
} /* namespace Service */
} /* namespace App */

#endif
