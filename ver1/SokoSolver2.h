#ifndef SOKO_SOLVER2_INCLUDED
#define SOKO_SOLVER2_INCLUDED

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

namespace puzzle {

typedef std::string Table;

class SokoSolver2 {
public:
  /*!
   * @brief Constructor
   * @param[in] board   '\n' separated map data.
   * @param[in] verbose Verbose mode.
   * @details
   * Call SetupBoard(), for setup analysis map.
   */
  SokoSolver2(const std::string board, const bool verbose = false);

  /*!
   * @brief Destructor
   */
  virtual ~SokoSolver2();

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
  uint64_t Elapsed() const { return elapsed_; }

private:
  /*!
   * @brief
   * @return Answer procedure, or "No solution." for no solution.
   * @details
   * Find a solution to a given map level.
   * For purpose of this task, PSPACE-complete problem may be used.
   *
   * "LRUD" is push box, "lrud" is move player.
   */
  std::string SolveMain();

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
  void SetupBoard(const std::string board);

  /*!
   * @brief Move player.
   * @param[in] x    Player X position.
   * @param[in] y    Player Y position.
   * @param[in] dx   Move direction X.
   * @param[in] dy   Move direction Y.
   * @param[in] data Current map.
   * @retval true  Success
   * @retval false Fail
   * @details
   * If player can move, move player on current map.
   */
  bool Move(const int x, const int y, const int dx, const int dy, Table& data);

  /*!
   * @brief Push box.
   * @param[in] x    Player X position.
   * @param[in] y    Player Y position.
   * @param[in] dx   Move direction X.
   * @param[in] dy   Move direction Y.
   * @param[in] data Current map.
   * @retval true  Success
   * @retval false Fail
   * @details
   * If player can push box, push box on current map.
   */
  bool Push(const int x, const int y, const int dx, const int dy, Table& data);

  /*!
   * @brief Check solved.
   * @param[in] data Current map.
   * @details
   * Check all boxes located on goal.
   */
  bool IsSolved(const Table& data);

  /*!
   * @brief Get array index.
   * @param[in] x X position.
   * @param[in] y Y position.
   * @return Array index.
   * @details
   * Calculate array index from position.
   */
  int GetArrayIndex(const int x, const int y) const;

  /*!
   * @brief Split string by delimiter.
   * @param[in] str   Target string.
   * @param[in] delim Delimiter character.
   * @return Delimitered string.
   * @details
   * To delimit string by delimiter.
   */
  std::vector<std::string> Split(const std::string& str, const char delim);

  void print_map(const Table& data);

private:
  std::vector<std::tuple<int, int, char, char>> dirs_;  //!< Direction information tuples (dx, dy, move, push).
  std::map<char, char> map_translate_chars_;  //!< Initial map characters.
  std::vector<std::tuple<int, int>> goals_;  //!< Goal positions (X, Y).
  Table       initial_map_;       //!< Initial map information.
  int         width_;             //!< Map width.
  int         height_;            //!< Map height.
  int         px_;                //!< Player initial X position.
  int         py_;                //!< Player initial Y position.

  // Solution statistics.
  std::string solution_;          //!< Solution procedure.
  uint64_t    looped_count_;      //!< Looped count for search.
  uint64_t    max_opened_count_;  //!< Max branch count on queue.
  uint64_t    visited_count_;     //!< Visited map pattern count.
  uint64_t    elapsed_;           //!< Elpased time (millisecond).
  bool        verbose_;           //!< Verbose mode.
};

}  // puzzle

#endif  // SOKO_SOLVER2_INCLUDED
