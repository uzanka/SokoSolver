#include "MovableDrawer.h"

///////////////////////////////////////////////////////////////////////////////
MovableDrawer::MovableDrawer() {
}

///////////////////////////////////////////////////////////////////////////////
MovableDrawer::~MovableDrawer() {
}

///////////////////////////////////////////////////////////////////////////////
void MovableDrawer::DrawRecursive(Table& table, const int x, const int y) {
  table.Set(x, y, kPlayer);
  if (table.Get(x + 1, y) == kSpace) DrawRecursive(table, x + 1, y);
  if (table.Get(x - 1, y) == kSpace) DrawRecursive(table, x - 1, y);
  if (table.Get(x, y + 1) == kSpace) DrawRecursive(table, x, y + 1);
  if (table.Get(x, y - 1) == kSpace) DrawRecursive(table, x, y - 1);
}
