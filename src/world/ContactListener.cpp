#include "world/ContactListener.hpp"

#include <iostream>

namespace GameCore {
namespace World {

void ContactListener::BeginContact(b2Contact* contact) {
  std::cout << "BeginContact" << std::endl;
}

void ContactListener::EndContact(b2Contact* contact) {
  std::cout << "EndContact" << std::endl;
}

} /* namespace World */
} /* namespace GameCore */
