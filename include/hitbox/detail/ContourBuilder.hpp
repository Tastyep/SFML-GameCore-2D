#ifndef HITBOX_BUILER_CONTOUR_BUILDER_HPP
#define HITBOX_BUILER_CONTOUR_BUILDER_HPP

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace GameCore {
namespace Hitbox {
namespace Detail {

class ContourBuilder {
 private:
  enum class StepDirection { None, N, W, S, E };

  const uint8_t alphaThreshold = 10;
  const std::array<StepDirection, 16> directions{ {
    StepDirection::None,
    StepDirection::N,
    StepDirection::E,
    StepDirection::E,
    StepDirection::W,
    StepDirection::N,
    StepDirection::None,
    StepDirection::E,
    StepDirection::S,
    StepDirection::None,
    StepDirection::S,
    StepDirection::S,
    StepDirection::W,
    StepDirection::N,
    StepDirection::W,
    StepDirection::None,
  } };

 public:
  std::vector<sf::Vector2i> make(const sf::Sprite& sprite) const;

 private:
  sf::Vector2i findStartPoint() const;
  std::vector<sf::Vector2i> walkPerimeter(const sf::Vector2i& start) const;
  void step(std::vector<sf::Vector2i>& contour, const sf::Vector2i& point, StepDirection& nextStep) const;
  void savePoint(std::vector<sf::Vector2i>& contour, const sf::Vector2i& p) const;
  int pixelState(const sf::Vector2i& p) const;
  bool isPixelSolid(int x, int y) const;
  bool isPixelSolid(const sf::Vector2i& p) const {
    return this->isPixelSolid(p.x, p.y);
  }

 private:
  mutable sf::Image* _image;
  mutable sf::IntRect _bound;
};

} /* namespace Detail */
} /* namespace Hitbox */
} /* namespace GameCore */

#endif
