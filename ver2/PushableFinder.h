#ifndef PUSHABLE_FINDER_INCLUDED
#define PUSHABLE_FINDER_INCLUDED

#include <list>
#include <tuple>
#include "Table.h"

///////////////////////////////////////////////////////////////////////////////
/*!
 * @brief Iterate pushable positions.
 */
class PushableFinder {
public:
  /*!
   * @brief Contructor
   * @param[in]  table      Map data.
   * @param[out] positions  Pushable positions.
   */
  PushableFinder();

  /*!
   * @brief Destructor
   */
  ~PushableFinder();

  static const int kUp;
  static const int kRight;
  static const int kDown;
  static const int kLeft;

  /*!
   * @brief Iterate pushable positions.
   * @param[in]  table      Map data.
   * @param[out] positions  Pushable positions.
   * @details
   * Iterate pushable positions.
   */
  static void Pushable(Table& table, std::list<std::tuple<int, int, int>>& positions);
  static void Pushable2(Table& table, std::list<std::tuple<int, int, int>>& positions, Table& deadzone);

protected:
  /*!
   * @brief 
   * @param[in] value1  1st value.
   * @param[in] value2  2nd value.
   * @retval true  Pushable
   * @retval false Unpushable
   * @details
   * Check pushable box.
   */
  static bool Pushable(const int value1, const int value2);
};

#endif  // PUSHABLE_FINDER_INCLUDED
