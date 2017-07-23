#include "world/physic/Polygon.hpp"

namespace GameCore {
namespace World {
namespace Physic {

Polygon::Polygon(std::vector<sf::Vector2f> vertices) {
  this->operator=(std::move(vertices));
}

Polygon& Polygon::operator=(std::vector<sf::Vector2f> vertices) {
  _vertices = std::move(vertices);
  _originTranslation = _vertices.front();
  size_t nbVertices = _vertices.size();

  for (size_t i = nbVertices - 1, j = 0; j < nbVertices; i = j, ++j) {
    const auto& direction = _vertices[j] - _vertices[i];
    sf::Vector2f normal{ direction.y, direction.x };

    normal /= std::sqrt(normal.x * normal.x + normal.y * normal.y);
    _normals.push_back(normal);
  }

  this->refresh();
  return *this;
}

const std::vector<sf::Vector2f>& Polygon::vertices() const {
  return _vertices;
}

const std::vector<sf::Vector2f>& Polygon::normals() const {
  return _normals;
}

void Polygon::move(const sf::Vector2f& distance) {
  for (auto& p : _vertices) {
    p += distance;
  }
  this->refresh();
}

void Polygon::setPosition(const sf::Vector2f& position) {
  sf::Vector2f firstVertice = _vertices.front();

  for (auto& vertice : _vertices) {
    vertice = position + (vertice - firstVertice) + _originTranslation;
  }
  this->refresh();
}

void Polygon::draw(sf::RenderTarget& target, sf::RenderStates) const {
  target.draw(_vertexArray);
}

void Polygon::refresh() {
  sf::VertexArray vertices(sf::PrimitiveType::LineStrip, 0);
  size_t nbVertices = _vertices.size();

  for (size_t i = 0; i < nbVertices + 1; ++i) {
    const auto& p = _vertices[i % nbVertices];
    vertices.append(sf::Vertex(p, sf::Color::Black));
  }
  _vertexArray = std::move(vertices);
}

} /* namespace Physic */
} /* namespace World */
} /* namespace GameCore */
