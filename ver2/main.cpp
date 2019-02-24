#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include "Table8.h"
#include "Table2.h"
#include "SokoSolver.h"

///////////////////////////////////////////////////////////////////////////////
void Usage() {
  std::cout << "Usage: SokoSolver.exe [-verbose] [-timeout {second}] {filename}" << std::endl;
  std::cout << "  {filename}  Input map from specified filename." << std::endl;
  std::cout << "  -verbose    Enable verbose mode." << std::endl;
  std::cout << "  -timeout    If solution can not be found, cancel." << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
bool ParseArgs(
  int argc, char** argv,
  std::string& filename,
  bool& verbose,
  int& timeout) {
  for (int i = 1; i < argc; i++) {
    std::string option = argv[i];
    if (option == "-verbose" || option == "-v") {
      verbose = true;
    } else if (option == "-timeout" || option == "-t") {
      i++;
      if (i < argc) {
        timeout = atoi(argv[i]);
      }
    } else {
      filename = option;
    }
  }
  if (filename.empty()) {
    return false;
  }
  if (timeout < 0) {
    return false;
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////
std::vector<std::string> ReadFile(const std::string filename) {
  std::vector<std::string> board;
  std::ifstream ifs(filename);
  if (ifs) {
    std::string buffer;
    while (std::getline(ifs, buffer)) {
      if (!buffer.empty()) {
        board.push_back(buffer);
      }
    }
  }
  return board;
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
  std::string filename;
  bool verbose = false;
  int timeout = 0;
  if (!ParseArgs(argc, argv, filename, verbose, timeout)) {
    Usage();
    return 1;
  }

  std::vector<std::string> board = ReadFile(filename);
  if (board.empty()) {
    Usage();
    return 1;
  }

  for (auto& data : board) {
    std::cout << data << std::endl;
  }
  std::cout << std::endl;

  std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

  SokoSolver solver(board, verbose, timeout);
  std::string answer;
  try {
    answer = solver.Solve();
    std::cout << answer << std::endl;
  } catch (std::exception& exc) {
    std::cout << "Exception: " + std::string(exc.what()) << std::endl;
  }

  //if (verbose) {
    std::cout << "count=" + std::to_string(solver.LoopedCount()) + " open=" + std::to_string(solver.MaxOpenedCount()) + " visited=" + std::to_string(solver.VisitedCount()) << std::endl;
    if (answer.substr(0, 1) == "(") {
      std::cout << "Push=" + std::to_string(std::count(answer.begin(), answer.end(), '(')) << std::endl;
    }
  //}

  std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
  uint64_t elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << std::to_string(elapsed) + " msec." << std::endl;

  return 0;
}
