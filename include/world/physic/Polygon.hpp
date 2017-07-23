#ifndef GAME_CORE_WORLD_PHYSIC_POLYGON_HPP
#define GAME_CORE_WORLD_PHYSIC_POLYGON_HPP

#include <cmath>
#include <cstddef>
#include <utility>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameCore {
namespace World {
namespace Physic {

class Polygon : public sf::Drawable {
 public:
  Polygon() = default;
  explicit Polygon(std::vector<sf::Vector2f> vertices);

  Polygon& operator=(std::vector<sf::Vector2f> vertices);

  const std::vector<sf::Vector2f>& vertices() const;
  const std::vector<sf::Vector2f>& normals() const;

 public:
  void move(const sf::Vector2f& distance);
  void setPosition(const sf::Vector2f& position);

 public:
  void draw(sf::RenderTarget& target, sf::RenderStates) const override;

  void refresh();

 private:
  std::vector<sf::Vector2f> _vertices;
  std::vector<sf::Vector2f> _normals;
  sf::Vector2f _originTranslation;

 private:
  sf::VertexArray _vertexArray;
};

} /* namespace Physic */
} /* namespace World */
} /* namespace GameCore */

#endif
