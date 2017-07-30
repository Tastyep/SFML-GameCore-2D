#ifndef GAME_CORE_WORLD_CORE_HPP
#define GAME_CORE_WORLD_CORE_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>

#include "world/Camera.hpp"
#include "world/Grid.hpp"
#include "world/entity/Factory.hpp"
#include "world/physic/Polygon.hpp"

namespace GameCore {
namespace World {

class Core : public sf::Drawable {
 public:
  Core(std::unique_ptr<Entity::Factory> entityFactory, const sf::FloatRect& viewRect);

  void draw(sf::RenderTarget& target, sf::RenderStates) const override;

  bool loadMap(const std::string& file);

 private:
  std::unique_ptr<Entity::Factory> _entityFactory;
  Grid _grid;
  Camera _camera;
};

} /* namespace World */
} /* namespace GameCore */

#endif
