#include "Evaluator.h"

libchess::Move Evaluator::getBestMove(libchess::Position position) {
  this->position = position;
  int bestScore = position.turn() == libchess::White ? std::numeric_limits<int>::lowest() : std::numeric_limits<int>::max();
  libchess::Move bestMove;
  bool maximizingPlayer = position.turn() == libchess::White;

  auto moves = position.legal_moves(); 
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(moves.begin(), moves.end(), std::default_random_engine(seed));

  for (const auto& move : moves) { 
    this->position.makemove(move);
    
    int score = alphaBeta(/* depth = */ 4, std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max(), !maximizingPlayer);
    this->position.undomove();
    if ((maximizingPlayer && score > bestScore) || (!maximizingPlayer && score < bestScore)) {
      bestScore = score;
      bestMove = move;
    }
  }
  return bestMove;
}

int Evaluator::alphaBeta(int depth, int alpha, int beta, bool maximizingPlayer) {
  if (depth == 0) {
    return evaluate();
  }

  auto moves = position.legal_moves(); 

  if (maximizingPlayer) {
    int maxEval = std::numeric_limits<int>::lowest();
    for (const auto& move : moves) {
      position.makemove(move);
      int eval = alphaBeta(depth - 1, alpha, beta, false);
      position.undomove();
      maxEval = std::max(maxEval, eval);
      alpha = std::max(alpha, eval);
      if (beta <= alpha) {
        break; // Beta cutoff
      }
    }
    return maxEval;
  } else {
    int minEval = std::numeric_limits<int>::max();
    for (const auto& move : moves) {
      position.makemove(move);
      int eval = alphaBeta(depth - 1, alpha, beta, true);
      position.undomove();
      minEval = std::min(minEval, eval);
      beta = std::min(beta, eval);
      if (beta <= alpha) {
        break; // Alpha cutoff
      }
    }
    return minEval;
  }
}

int Evaluator::evaluate() {
  // High positive value for checkmate in favor of white, and high negative value for black.
  const int checkmateScore = 100000;
  const int drawScore = 0;
  const int checkScore = 50;

  // Check for checkmate or draw conditions
  if (position.is_checkmate()) {
      if (position.turn() == libchess::White) {
          return -checkmateScore; // Black wins
      } else {
          return checkmateScore; // White wins
      }
  } else if (position.is_stalemate() || position.is_draw()) {
      return drawScore; // Drawn game
  }

  int score = 0;
  
  score += getPiecesScore();

  if (position.in_check()) {
    // Apply check score. Positive for White's perspective, negative if it's Black's turn to move.
    score += position.turn() == libchess::White ? -checkScore : checkScore;
  }

  return score;
}

int Evaluator::getPiecesScore() {
  constexpr int PawnValue = 100;
  constexpr int KnightValue = 320;
  constexpr int BishopValue = 330;
  constexpr int RookValue = 500;
  constexpr int QueenValue = 900;
  int score = 0;

  score += position.pieces(libchess::Side::White, libchess::Piece::Pawn).count() * PawnValue;
  score += position.pieces(libchess::Side::White, libchess::Piece::Knight).count() * KnightValue;
  score += position.pieces(libchess::Side::White, libchess::Piece::Bishop).count() * BishopValue;
  score += position.pieces(libchess::Side::White, libchess::Piece::Rook).count() * RookValue;
  score += position.pieces(libchess::Side::White, libchess::Piece::Queen).count() * QueenValue;

  score -= position.pieces(libchess::Side::Black, libchess::Piece::Pawn).count() * PawnValue;
  score -= position.pieces(libchess::Side::Black, libchess::Piece::Knight).count() * KnightValue;
  score -= position.pieces(libchess::Side::Black, libchess::Piece::Bishop).count() * BishopValue;
  score -= position.pieces(libchess::Side::Black, libchess::Piece::Rook).count() * RookValue;
  score -= position.pieces(libchess::Side::Black, libchess::Piece::Queen).count() * QueenValue;

  return score;
}
