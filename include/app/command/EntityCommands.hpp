#ifndef GAME_CORE_APP_COMMAND_ENTITY_COMMANDS_HPP
#define GAME_CORE_APP_COMMAND_ENTITY_COMMANDS_HPP

#include "boost/mpl/vector.hpp"

#include "PlayRho/Common/Vector2D.hpp"
#include "PlayRho/Common/Velocity.hpp"

#include "world/entity/EntityId.hpp"

namespace GameCore {
namespace App {
namespace Command {

class AddEntity {
 public:
  AddEntity(World::Entity::Id entityId, playrho::Length2D position, playrho::LinearVelocity2D velocity)
    : _entityId(entityId)
    , _position(position)
    , _velocity(velocity) {}

  World::Entity::Id entityId() const {
    return _entityId;
  }

  playrho::Length2D position() const {
    return _position;
  }

  playrho::LinearVelocity2D velocity() const {
    return _velocity;
  }

 private:
  World::Entity::Id _entityId;
  playrho::Length2D _position;
  playrho::LinearVelocity2D _velocity;
};

using EntityCommands = boost::mpl::vector1<AddEntity>;

} /* namespace Command */
} /* namespace App */
} /* namespace GameCore */

#endif
