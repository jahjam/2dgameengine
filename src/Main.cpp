#include "Game/Game.h"
#include "easylogging++.h"

// This is to initialise the logger
// and only needs to be used one here
INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]) {
  el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
  Game game;

  game.initialise();
  game.run();
  game.destroy();

  return 0;
}
