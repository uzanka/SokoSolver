#include "UnmovableFinder.h"

///////////////////////////////////////////////////////////////////////////////
UnmovableFinder::UnmovableFinder() {
}

///////////////////////////////////////////////////////////////////////////////
UnmovableFinder::~UnmovableFinder() {
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Unmovable(const Table& table, const GoalsHolder& goals, const int x, const int y) {
  if (table.Get(x, y) == kBox) {
    if (Check1(table, goals, x, y)) {
      return true;
    }
    if (Check2(table, goals, x, y)) {
      return true;
    }
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check1(const Table& table, const GoalsHolder& goals, const int x, const int y) {
  // #   $#   #  #$
  // $#  #   #$   #

  if (table.Get(x, y) != kBox) return false;
  if (goals.Goal(x, y)) return false;

  if ((table.Get(x + 1, y) == kWall) && (table.Get(x, y - 1) == kWall)) return true;
  if ((table.Get(x + 1, y) == kWall) && (table.Get(x, y + 1) == kWall)) return true;
  if ((table.Get(x - 1, y) == kWall) && (table.Get(x, y - 1) == kWall)) return true;
  if ((table.Get(x - 1, y) == kWall) && (table.Get(x, y + 1) == kWall)) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check2(const Table& table, const GoalsHolder& goals, const int x, const int y) {
  // C#  $C  #$  ##
  // $#  ##  #C  C$

  if (table.Get(x, y) != kBox) return false;
  if (goals.Goal(x, y)) return false;

  if ((table.Get(x + 1, y) == kWall) && (table.Get(x + 1, y + 1) == kWall)
    && (table.Get(x, y + 1) == kBox)) return true;
  if ((table.Get(x, y + 1) == kWall) && (table.Get(x + 1, y - 1) == kWall)
    && (table.Get(x - 1, y) == kBox)) return true;
  if ((table.Get(x - 1, y) == kWall) && (table.Get(x - 1, y - 1) == kWall)
    && (table.Get(x, y - 1) == kBox)) return true;
  if ((table.Get(x, y - 1) == kWall) && (table.Get(x + 1, y - 1) == kWall)
    && (table.Get(x + 1, y) == kBox)) return true;

  // $#  C$  #C  ##
  // C#  ##  #$  $C

  if ((table.Get(x + 1, y) == kWall) && (table.Get(x + 1, y - 1) == kWall)
    && (table.Get(x, y - 1) == kBox)) return true;
  if ((table.Get(x, y + 1) == kWall) && (table.Get(x + 1, y + 1) == kWall)
    && (table.Get(x + 1, y) == kBox)) return true;
  if ((table.Get(x - 1, y) == kWall) && (table.Get(x - 1, y + 1) == kWall)
    && (table.Get(x, y + 1) == kBox)) return true;
  if ((table.Get(x, y - 1) == kWall) && (table.Get(x - 1, y - 1) == kWall)
    && (table.Get(x - 1, y) == kBox)) return true;

  return false;
}
