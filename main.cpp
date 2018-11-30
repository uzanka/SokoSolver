#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include "SokoSolver.h"
#include "SokoSolver2.h"

///////////////////////////////////////////////////////////////////////////////
void Usage() {
  std::cout << "Usage: SokoSolver.exe [-input {filename} | -stdin] [-verbose]" << std::endl;
  std::cout << "  -input    Input map from filename." << std::endl;
  std::cout << "  -stdin    Input map from stdin." << std::endl;
  std::cout << "  -verbose  Enable verbose mode." << std::endl;
  std::cout << "  -2        Solver type." << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
std::string ReadFile(const std::string filename) {
  std::ifstream ifs(filename);
  if (!ifs) {
    return "";
  }

  std::string level;
  std::string buffer;
  while (std::getline(ifs, buffer)) {
    if (!level.empty()) {
      level += "\n";
    }
    level += buffer;
  }

  return level;
}

///////////////////////////////////////////////////////////////////////////////
std::string ReadStdin() {
  std::string level;
  std::string buffer;
  while (std::getline(std::cin, buffer)) {
    if (!level.empty()) {
      level += "\n";
    }
    level += buffer;
  }
  return level;
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
  std::string filename;
  bool verbose = false;
  int type = 1;
  for (int i = 1; i < argc; i++) {
    std::string option = argv[i];
    if (option == "-verbose" || option == "-v") {
      verbose = true;
    } else if (option == "-input" || option == "-i") {
      if (++i < argc) {
        filename = argv[i];
      } else {
        Usage();
        return 1;
      }
    } else if (option == "-stdin") {
      filename = "-stdin";
    } else if (option == "-2") {
      type = 2;
    } else if (option.substr(0, 1) != "-") {
      filename = option;
    } else {
      Usage();
      return 1;
    }
  }

  std::string level;
  if (filename == "-stdin") {
    level = ReadStdin();
  } else if (!filename.empty()) {
    level = ReadFile(filename);
  } else {
    Usage();
    return 1;
  }
  if (level.empty()) {
    Usage();
    return 1;
  }

  if (type == 1) {
    std::cout << level << std::endl;
    puzzle::SokoSolver board(level, verbose);
    std::cout << board.Solve() << std::endl;

    if (verbose) {
      std::cout << "count=" + std::to_string(board.LoopedCount()) + " open=" + std::to_string(board.MaxOpenedCount()) + " visited=" + std::to_string(board.VisitedCount()) << std::endl;
      std::cout << std::to_string(board.Elapsed()) + " msec." << std::endl;
    }
  } else if (type == 2) {
    std::cout << level << std::endl;
    puzzle::SokoSolver2 board(level, verbose);
    std::cout << board.Solve() << std::endl;

    if (verbose) {
      std::cout << "count=" + std::to_string(board.LoopedCount()) + " open=" + std::to_string(board.MaxOpenedCount()) + " visited=" + std::to_string(board.VisitedCount()) << std::endl;
      std::cout << std::to_string(board.Elapsed()) + " msec." << std::endl;
    }
  }

  return 0;
}
