#ifndef GAME_CORE_WORLD_ENTITY_ENTITY_MANAGER_HPP
#define GAME_CORE_WORLD_ENTITY_ENTITY_MANAGER_HPP

#include <memory>
#include <vector>

#include "world/entity/Entity.hpp"

namespace World {
namespace Entity {

class Manager {
 public:
  void add(std::shared_ptr<Entity> entity);
  const std::vector<std::shared_ptr<Entity>> list() const;
  void clear();

 private:
  std::vector<std::shared_ptr<Entity>> _entities;
};

} /* namespace Entity */
} /* namespace World */

#endif
