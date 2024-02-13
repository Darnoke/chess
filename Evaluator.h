#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "libchess/src/libchess/position.hpp"

class Evaluator {
public:
  libchess::Move getBestMove(libchess::Position position);

private:
  libchess::Position position;
  int alphaBeta(int depth, int alpha, int beta, bool maximizingPlayer);
  int evaluate();
  int getPiecesScore();
};

#endif // EVALUATOR_H
