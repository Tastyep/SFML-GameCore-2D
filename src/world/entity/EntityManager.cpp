#include "world/entity/EntityManager.hpp"

#include <utility>

namespace GameCore {
namespace World {
namespace Entity {

void Manager::add(std::shared_ptr<Entity> entity) {
  _entities.push_back(std::move(entity));
}

const std::vector<std::shared_ptr<Entity>> Manager::list() const {
  return _entities;
}

void Manager::clear() {
  _entities.clear();
}

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */
