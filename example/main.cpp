#include "TaskManager/Module.hpp"

#include "Core.hpp"

int main() {
  Task::Module::init(4);
  Core game;

  game.run();
  return 0;
}
