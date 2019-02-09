#ifndef SOKO_SOLVER_INCLUDED
#define SOKO_SOLVER_INCLUDED

#include <string>
#include <vector>
#include <map>
#include <list>
#include <limits>
#include <unordered_set>
#include <queue>
#include <sstream>
#include <iostream>
#include <chrono>
#include "Table.h"
#include "GoalsHolder.h"
#include "DeadzoneFinder.h"
#include "UnmovableFinder.h"

class SokoSolver {
public:
  /*!
   * @brief Constructor
   * @param[in] board    Map data.
   * @param[in] verbose  Verbose mode.
   * @details
   * Call SetupBoard(), for setup analysis map.
   */
  SokoSolver(const std::vector<std::string>& board, const bool verbose = false, const int timeout = 0);

  /*!
   * @brief Destructor
   */
  virtual ~SokoSolver();

  /*!
   * @brief 
   * @return Answer procedure, or "No solution." for no solution.
   * @details
   * Call SolveMain(), for solve.
   */
  std::string Solve();

  std::string Solution() const { return solution_; }
  uint64_t LoopedCount() const { return looped_count_; }
  uint64_t MaxOpenedCount() const { return max_opened_count_; }
  uint64_t VisitedCount() const { return visited_count_; }

private:
  /*!
   * @brief Setup analysis map.
   * @param[in] board '\n' separated map data.
   * @details
   * Make initial map to initial_map_.
   * Make goals tuples to goals_.
   * Store map size to width_, heigth_.
   * Store player position to px_, py_.
   *
   * @example
   * "######  \n"
   * "#    ###\n"
   * "# #$$$ #\n"
   * "#.     #\n"
   * "#. ##  #\n"
   * "#**..$ #\n"
   * "##@   ##\n"
   * "######  "
   *
   * " ": space
   * "#": wall
   * ".": goal
   * "$": box
   * "@": player
   * "*": box on goal
   * "+": player on goal
   */
  void SetupBoard(const std::vector<std::string>& board);

  /*!
   * @brief Push box.
   * @param[in] x    Player X position.
   * @param[in] y    Player Y position.
   * @param[in] dx   Move direction X.
   * @param[in] dy   Move direction Y.
   * @param[in] table Current map.
   * @retval true  Success
   * @retval false Fail
   * @details
   * If player can push box, push box on current map.
   */
  bool Push(Table& table, const int x, const int y, const int dx, const int dy);

  void print_map(const Table& table);

private:
  std::vector<std::tuple<int, int, char, char>> dirs_;  //!< Direction information tuples (dx, dy, move, push).
  GoalsHolder goals_;             //!< Goal positions (X, Y).
  Table       initial_map_;       //!< Initial map information.
  //DeadzoneFinder deadzone_;
  Table       deadzone_;
  UnmovableFinder unmovable_;
  int         width_;             //!< Map width.
  int         height_;            //!< Map height.
  int         px_;                //!< Player initial X position.
  int         py_;                //!< Player initial Y position.

  // Solution statistics.
  std::string solution_;          //!< Solution procedure.
  uint64_t    looped_count_;      //!< Looped count for search.
  uint64_t    max_opened_count_;  //!< Max branch count on queue.
  uint64_t    visited_count_;     //!< Visited map pattern count.
  bool        verbose_;           //!< Verbose mode.
  int         timeout_;
  std::chrono::system_clock::time_point start_;
};

#endif  // SOKO_SOLVER_INCLUDED
