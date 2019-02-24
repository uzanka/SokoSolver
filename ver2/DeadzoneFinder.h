#ifndef DEADZONE_FINDER_INCLUDED
#define DEADZONE_FINDER_INCLUDED

#include <vector>
#include <tuple>
#include "Table.h"
#include "GoalsHolder.h"

///////////////////////////////////////////////////////////////////////////////
class Pattern {
public:
  /*!
   * @brief Contructor
   */
  Pattern() {}

  /*!
   * @brief Destructor
   */
  virtual ~Pattern() {}

  /*!
   * @brief Add position.
   * @param[in] position tuple(x, y, value)
   * @details
   * Add check position to map.
   */
  void Add(std::tuple<int, int, int> position) {
    positions_.push_back(position);
  }

  std::vector<std::tuple<int, int, int>> positions_;  //!< (x, y, value)
};

///////////////////////////////////////////////////////////////////////////////
/*!
 * @brief Check unmovable pattern.
 */
class DeadzoneFinder {
public:
  /*!
   * @brief Contructor
   */
  DeadzoneFinder();

  /*!
   * @brief Destructor
   */
  ~DeadzoneFinder();

  /*!
   * @brief Iterate pushable positions.
   * @param[in] table  Map data.
   * @details
   * Check unmovable pattern.
   */
  void Initialize(const Table& table, const GoalsHolder& goals, Table& deadzone);
  bool Deadzone(const int x, const int y);

protected:
  void Add(Pattern pattern) {
    patterns_.push_back(pattern);
  }

  void Type11();
  void Type12();
  void Type21();
  void Type22();
  void Type23();
  void Type24();
  void Type31();
  void Type32();
  void Type33();
  void Type34();
  void Type41();
  void Type42();
  void Type51();
  void Type61();
  void Type71();
  void Type81();
  void Type91();

protected:
  std::vector<Pattern> patterns_;
  Table deadzone_;
};

#endif  // DEADZONE_FINDER_INCLUDED
