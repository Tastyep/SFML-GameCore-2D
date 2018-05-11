#ifndef GAME_CORE_GAME_RESSOURCES_TILE_PARSER_HPP
#define GAME_CORE_GAME_RESSOURCES_TILE_PARSER_HPP

#include <type_traits>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>

namespace Ressource {

class TileManager {
 public:
  size_t parse(const sf::Texture& texture, size_t tileSize);
  const std::vector<sf::Sprite>& tiles() const;

  template <typename Id, typename = std::enable_if_t<std::is_enum<Id>::value, Id>>
  const sf::Sprite& tile(Id id) const {
    return _tiles[static_cast<size_t>(id)];
  }

 private:
  std::vector<sf::Sprite> _tiles;
};

} /* namespace Ressource */

#endif
