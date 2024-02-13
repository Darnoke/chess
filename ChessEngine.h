#ifndef CHESSENGINE_H
#define CHESSENGINE_H

#include <string>
#include <sstream>
#include "libchess/src/libchess/position.hpp"
#include "Evaluator.h"

class ChessEngine {
public:
  void run();

private:
  libchess::Position position;
  void handleUci();
  void handleIsReady();
  void handleSetOption(std::istringstream& iss);
  void handleUciNewGame();
  void handlePosition(std::istringstream& iss);
  void handleGo();
};

#endif // CHESSENGINE_H
