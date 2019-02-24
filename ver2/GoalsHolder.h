#ifndef GOALS_HOLDER_INCLUDED
#define GOALS_HOLDER_INCLUDED

#include <map>
#include <vector>
#include <tuple>
#include "Table.h"

///////////////////////////////////////////////////////////////////////////////
/*!
 * @brief Goals holder.
 */
class GoalsHolder {
public:
  /*!
   * @brief Contructor
   */
  GoalsHolder();

  /*!
   * @brief Destructor
   */
  ~GoalsHolder();

  void Clear();

  void Size(const int width, const int height);
  void Add(const int x, const int y);

  bool Goal(const int x, const int y) const;

  bool Solved(const Table& table) const;

  void GetGoals(std::vector<std::tuple<int, int>>& goal_xy) const;

protected:
  int GetMapKey(const int x, const int y) const;

protected:
  std::vector<std::tuple<int, int>> goal_xy_;
  std::map<int, int> goals_;
  int width_;
  int height_;
};

#endif  // GOALS_HOLDER_INCLUDED
