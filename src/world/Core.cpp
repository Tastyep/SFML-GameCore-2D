#include "world/Core.hpp"

#include <utility>

namespace GameCore {
namespace World {

Core::Core(std::unique_ptr<Entity::Factory> entityFactory)
  : _entityFactory(std::move(entityFactory)) {}

} /* namespace World */
} /* namespace GameCore */
