#include "TaskManager/Module.hh"

#include "Core.hpp"

int main() {
  Task::Module::init(4);
  GameCore::Core game;

  game.run();
  return 0;
}
