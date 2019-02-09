#ifndef MOVABLE_DRAWER_INCLUDED
#define MOVABLE_DRAWER_INCLUDED

#include "Table.h"

///////////////////////////////////////////////////////////////////////////////
/*!
 * @brief Draw movable area.
 */
class MovableDrawer {
public:
  /*!
   * @brief Contructor
   * @param[in,out] table  Map data.
   */
  MovableDrawer();

  /*!
   * @brief Destructor
   */
  ~MovableDrawer();

  /*!
   * @brief Draw movable area.
   * @param[in,out] table  Map data.
   * @param[in]     px     Player x position.
   * @param[in]     py     Player y position.
   */
  static void DrawRecursive(Table& table, const int px, const int py);
};

#endif  // MOVABLE_DRAWER_INCLUDED
