#include <chrono>
#include <cmath>
#include <tuple>
#include <utility>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>

using namespace std::literals::chrono_literals;

class Window {
 public:
  Window()
    : _window(sf::VideoMode(1000, 1000), "GameCore") {
    _window.setFramerateLimit(30);
  }

  void run() {
    sf::Event event;

    while (_window.isOpen()) {
      while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          this->close();
        }
      }

      _window.display();
    }
  }

  void close() {
    _window.close();
  }

 private:
  sf::RenderWindow _window;
};

int main() {
  Window window;

  window.run();
  return 0;
}
