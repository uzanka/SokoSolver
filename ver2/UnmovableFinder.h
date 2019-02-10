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
  bool Check11(const Table& table, const int x, const int y);
  bool Check21(const Table& table, const int x, const int y);
  bool Check22(const Table& table, const int x, const int y);
  bool Check31(const Table& table, const int x, const int y);
  bool Check41(const Table& table, const int x, const int y);
};

#endif  // UNMOVABLE_FINDER_INCLUDED
