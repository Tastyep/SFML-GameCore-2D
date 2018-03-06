#ifndef GAME_CORE_WORLD_ENTITY_WALL_HPP
#define GAME_CORE_WORLD_ENTITY_WALL_HPP

#include "world/entity/Entity.hpp"

namespace GameCore {
namespace World {
namespace Entity {

class Wall : public Entity {
 public:
  Wall(playrho::Body* body, const sf::Sprite& sprite);

  void dispatchContact(const ContactHandler& handler, Entity& entity) override;
  void dispatchContact(Player& player, const ContactHandler& handler) override;
  void dispatchContact(Ball& ball, const ContactHandler& handler) override;

  void update() override;
  const std::string& name() const override;

 private:
  const std::string _name = "Wall";
};

} /* namespace Entity */
} /* namespace World */
} /* namespace GameCore */

#endif
