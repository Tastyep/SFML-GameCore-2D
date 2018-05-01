#ifndef GAME_CORE_WORLD_CORE_HPP
#define GAME_CORE_WORLD_CORE_HPP

#include <memory>
#include <mutex>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>

#include "PlayRho/Common/Math.hpp"
#include "PlayRho/Dynamics/StepConf.hpp"
#include "PlayRho/Dynamics/World.hpp"

#include "world/Camera.hpp"
#include "world/contact/ContactListener.hpp"
#include "world/entity/EntityId.hpp"
#include "world/entity/EntityManager.hpp"
#include "world/entity/Factory.hpp"

namespace GameCore {
namespace World {

class Core : public sf::Drawable {
 public:
  Core(std::unique_ptr<Entity::Factory> entityFactory, const sf::FloatRect& viewRect);

  void update();
  void draw(sf::RenderTarget& target, sf::RenderStates) const override;

  bool loadMap(const std::string& file);

  bool addEntity(Entity::Id entityId, playrho::Length2D position, playrho::LinearVelocity2D velocity);

 private:
  std::shared_ptr<playrho::World> _world;
  playrho::StepConf _stepConf;
  std::unique_ptr<Entity::Factory> _entityFactory;
  Contact::Listener _contactListener;
  Camera _camera;
  Entity::Manager _entityManager;
  mutable std::mutex _entityMutex;
};

} /* namespace World */
} /* namespace GameCore */

#endif
