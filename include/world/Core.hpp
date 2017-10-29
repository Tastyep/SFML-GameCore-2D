#ifndef GAME_CORE_WORLD_CORE_HPP
#define GAME_CORE_WORLD_CORE_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>

#include "PlayRho/Dynamics/StepConf.hpp"
#include "PlayRho/Dynamics/World.hpp"

#include "world/Camera.hpp"
#include "world/ContactListener.hpp"
#include "world/entity/Factory.hpp"
#include "world/physic/Polygon.hpp"

namespace GameCore {
namespace World {

class Core : public sf::Drawable {
 public:
  Core(std::unique_ptr<Entity::Factory> entityFactory, const sf::FloatRect& viewRect);

  void update();
  void draw(sf::RenderTarget& target, sf::RenderStates) const override;

  bool loadMap(const std::string& file);

 private:
  std::shared_ptr<playrho::World> _world;
  playrho::StepConf _stepConf;
  std::unique_ptr<Entity::Factory> _entityFactory;
  ContactListener _contactListener;
  Camera _camera;
  std::vector<std::shared_ptr<Entity::Entity>> _entities;
};

} /* namespace World */
} /* namespace GameCore */

#endif
