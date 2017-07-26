#ifndef GAME_CORE_WORLD_CORE_HPP
#define GAME_CORE_WORLD_CORE_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>

#include "world/entity/Factory.hpp"

namespace GameCore {
namespace World {

class Core : public sf::Drawable {
 public:
  Core(std::unique_ptr<Entity::Factory> entityFactory);

  void draw(sf::RenderTarget& target, sf::RenderStates) const override;

  bool loadMap(const std::string& file);

 private:
  std::unique_ptr<Entity::Factory> _entityFactory;
  std::vector<std::shared_ptr<Entity::Entity>> _entities;
};

} /* namespace World */
} /* namespace GameCore */

#endif
