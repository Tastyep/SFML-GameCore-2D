#ifndef GAME_CORE_WORLD_CORE_HPP
#define GAME_CORE_WORLD_CORE_HPP

#include <memory>

#include "world/entity/Factory.hpp"

namespace GameCore {
namespace World {

class Core {
 public:
  Core(std::unique_ptr<Entity::Factory> entityFactory);

  bool loadFromFile(const std::string& map);

 private:
  std::unique_ptr<Entity::Factory> _entityFactory;
};

} /* namespace World */
} /* namespace GameCore */

#endif
