#ifndef UNMOVABLE_FINDER_INCLUDED
#define UNMOVABLE_FINDER_INCLUDED

#include "Table.h"
#include "GoalsHolder.h"

///////////////////////////////////////////////////////////////////////////////
/*!
 * @brief Check unmovable pattern.
 */
class UnmovableFinder {
public:
  /*!
   * @brief Contructor
   */
  UnmovableFinder();

  /*!
   * @brief Destructor
   */
  ~UnmovableFinder();

  /*!
   * @brief Iterate pushable positions.
   * @param[in] table  Map data.
   * @retval true  Unmovable
   * @retval false Movable
   * @details
   * Check unmovable pattern.
   */
  bool Unmovable(const Table& table, const GoalsHolder& goals, const int x, const int y);

protected:
#ifdef CPPUTEST
public:
#endif
  // Current position is not goal.
  bool Check11(const Table& table, const int x, const int y);
  bool Check21(const Table& table, const int x, const int y);
  bool Check22(const Table& table, const int x, const int y);
  bool Check23(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check24(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check25(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check26(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check27(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check28(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check31(const Table& table, const int x, const int y);
  bool Check32(const Table& table, const int x, const int y);
  bool Check33(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check34(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check35(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check36(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check37(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check38(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check41(const Table& table, const int x, const int y);
  bool Check42(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check43(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check44(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check45(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check46(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check61(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check62(const Table& table, const GoalsHolder& goals, const int x, const int y);

  // Current position is goal.

  // Other patterns.
  bool Check2001(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check4001(const Table& table, const GoalsHolder& goals, const int x, const int y);
  bool Check4002(const Table& table, const GoalsHolder& goals, const int x, const int y);
};

#endif  // UNMOVABLE_FINDER_INCLUDED
