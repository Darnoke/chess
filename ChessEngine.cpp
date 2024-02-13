#include "ChessEngine.h"

void ChessEngine::run() {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::istringstream iss(line);
    std::string command;
    iss >> command;

    if (command == "uci") {
      handleUci();
    } else if (command == "isready") {
      handleIsReady();
    } else if (command == "setoption") {
      handleSetOption(iss);
    } else if (command == "ucinewgame") {
      handleUciNewGame();
    } else if (command == "position") {
      handlePosition(iss);
    } else if (command == "go") {
      handleGo();
    } else if (command == "quit") {
      break;
    }
  }
}

void ChessEngine::handleUci() {
  std::cout << "id name easyChess" << std::endl;
  std::cout << "id author 322945" << std::endl;
  // Send available options here
  std::cout << "uciok" << std::endl;
}

void ChessEngine::handleIsReady() {
  std::cout << "readyok" << std::endl;
}

void ChessEngine::handleSetOption(std::istringstream& iss) {
  // Parse and set options
  // Example: setoption name Hash value 128
  std::string token, optionName, optionValue;

  // Skip "name" token
  iss >> token;

  // Read the option name
  while (iss >> token && token != "value") {
    if (!optionName.empty()) {
      optionName += " ";
    }
    optionName += token;
  }

  // Read the option value
  while (iss >> token) {
    if (!optionValue.empty()) {
      optionValue += " ";
    }
    optionValue += token;
  }

  if (optionName == "Hash") {
    int hashSize = std::stoi(optionValue);
    // engine.setHashSize(hashSize);
    std::cout << "Not Set Hash to " << hashSize << std::endl;
  } else if (optionName == "SomeOtherOption") {
    // Handle other options
  } else {
    std::cout << "Warning: Unknown option " << optionName << std::endl;
  }
}

void ChessEngine::handleUciNewGame() {
  position = libchess::Position("startpos", true);
  // Initialize or reset the engine for a new game
}

void ChessEngine::handlePosition(std::istringstream& iss) {
  // Parse the position command and update the engine's internal board
  // Example: position startpos moves e2e4 e7e5
    std::string token, fen;
    iss >> token;

    if (token == "startpos") {
      position = libchess::Position("startpos", true);
      fen = "startpos";
      iss >> token; // Consume "moves" if present
    } else if (token == "fen") {
      while (iss >> token && token != "moves") {
        fen += token + " ";
      }
      position = libchess::Position{fen};
    }

    // Apply moves if any
    while (iss >> token) {
      position.makemove(token);
    }
}

void ChessEngine::handleGo() {
  // Start calculating and output the best move
  Evaluator evaluator;
  std::string bestMove = evaluator.getBestMove(position);
  std::cout << "bestmove " << bestMove << std::endl;
  position.makemove(bestMove);
}