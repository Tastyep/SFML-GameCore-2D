#include "ressource/TileManager.hpp"

#include <SFML/Graphics/Texture.hpp>

namespace GameCore {
namespace Ressource {

size_t TileManager::parse(const sf::Texture& texture, size_t tileSize) {
  const auto textureSize = texture.getSize();

  _tiles.clear();
  for (size_t y = 0; y + tileSize <= textureSize.y; y += tileSize) {
    for (size_t x = 0; x + tileSize <= textureSize.x; x += tileSize) {
      _tiles.emplace_back(texture, sf::IntRect{ static_cast<int>(x),        //
                                                static_cast<int>(y),        //
                                                static_cast<int>(tileSize), //
                                                static_cast<int>(tileSize) });
    }
  }
  return _tiles.size();
}

const std::vector<sf::Sprite>& TileManager::tiles() const {
  return _tiles;
}

} /* namespace Ressource */
} /* namespace GameCore */
