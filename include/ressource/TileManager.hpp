#ifndef GAME_CORE_GAME_RESSOURCES_TILE_PARSER_HPP
#define GAME_CORE_GAME_RESSOURCES_TILE_PARSER_HPP

#include <vector>

#include <SFML/Graphics/Sprite.hpp>

namespace GameCore {
namespace Ressource {

class TileManager {
 public:
  size_t parse(const sf::Texture& texture, size_t tileSize);
  const std::vector<sf::Sprite>& tiles() const;
  const sf::Sprite& tile(size_t index) const;

 private:
  std::vector<sf::Sprite> _tiles;
};

} /* namespace Ressource */
} /* namespace GameCore */

#endif
