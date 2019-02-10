#include "UnmovableFinder.h"

///////////////////////////////////////////////////////////////////////////////
UnmovableFinder::UnmovableFinder() {
}

///////////////////////////////////////////////////////////////////////////////
UnmovableFinder::~UnmovableFinder() {
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Unmovable(const Table& table, const GoalsHolder& goals, const int x, const int y) {
  if (table.Get(x, y) != kBox) return false;
  if (goals.Goal(x, y)) return false;

  if (Check11(table, x, y)) return true;
  if (Check21(table, x, y)) return true;
  if (Check22(table, x, y)) return true;
  if (Check31(table, x, y)) return true;
  if (Check41(table, x, y)) return true;
  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check11(const Table& table, const int x, const int y) {
  // #   $#   #  #$
  // $#  #   #$   #

  if ((table.Get(x + 1, y) == kWall) && (table.Get(x, y - 1) == kWall)) return true;
  if ((table.Get(x + 1, y) == kWall) && (table.Get(x, y + 1) == kWall)) return true;
  if ((table.Get(x - 1, y) == kWall) && (table.Get(x, y - 1) == kWall)) return true;
  if ((table.Get(x - 1, y) == kWall) && (table.Get(x, y + 1) == kWall)) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check21(const Table& table, const int x, const int y) {
  // C#  $C  #$  ##
  // $#  ##  #C  C$

  if ((table.Get(x + 1, y) == kWall) && (table.Get(x + 1, y + 1) == kWall)
   && (table.Get(x, y + 1) == kBox)) return true;
  if ((table.Get(x, y + 1) == kWall) && (table.Get(x - 1, y + 1) == kWall)
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

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check22(const Table& table, const int x, const int y) {
  // ?C#  #?  ?$#  #?
  // #$?  $C  #C?  C$
  //      ?#       ?#

  if ((table.Get(x + 1, y) == kWall) && (table.Get(x - 1, y + 1) == kWall)
   && (table.Get(x, y + 1) == kBox)) return true;
  if ((table.Get(x - 1, y - 1) == kWall) && (table.Get(x, y + 1) == kWall)
   && (table.Get(x - 1, y) == kBox)) return true;
  if ((table.Get(x + 1, y - 1) == kWall) && (table.Get(x - 1, y) == kWall)
   && (table.Get(x, y - 1) == kBox)) return true;
  if ((table.Get(x, y - 1) == kWall) && (table.Get(x + 1, y + 1) == kWall)
   && (table.Get(x + 1, y) == kBox)) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check31(const Table& table, const int x, const int y) {
  // C#  $C  $$  #$
  // $$  $#  #C  C$

  if ((table.Get(x + 1, y) == kWall)
   && (table.Get(x, y + 1) == kBox) && (table.Get(x + 1, y + 1) == kBox)) return true;
  if ((table.Get(x, y + 1) == kWall)
   && (table.Get(x - 1, y) == kBox) && (table.Get(x - 1, y + 1) == kBox)) return true;
  if ((table.Get(x - 1, y) == kWall)
   && (table.Get(x - 1, y - 1) == kBox) && (table.Get(x, y - 1) == kBox)) return true;
  if ((table.Get(x, y - 1) == kWall)
   && (table.Get(x + 1, y - 1) == kBox) && (table.Get(x + 1, y) == kBox)) return true;

  // #C  $#  $$  C$
  // $$  $C  C#  #$

  if ((table.Get(x - 1, y) == kWall)
   && (table.Get(x - 1, y + 1) == kBox) && (table.Get(x, y + 1) == kBox)) return true;
  if ((table.Get(x, y - 1) == kWall)
   && (table.Get(x - 1, y - 1) == kBox) && (table.Get(x - 1, y) == kBox)) return true;
  if ((table.Get(x + 1, y) == kWall)
   && (table.Get(x, y - 1) == kBox) && (table.Get(x + 1, y - 1) == kBox)) return true;
  if ((table.Get(x, y + 1) == kWall)
   && (table.Get(x + 1, y) == kBox) && (table.Get(x + 1, y + 1) == kBox)) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check41(const Table& table, const int x, const int y) {
  // C$  $C  $$  $$
  // $$  $$  $C  C$

  if ((table.Get(x + 1, y) == kBox)
   && (table.Get(x, y + 1) == kBox) && (table.Get(x + 1, y + 1) == kBox)) return true;
  if ((table.Get(x, y + 1) == kBox)
   && (table.Get(x - 1, y) == kBox) && (table.Get(x - 1, y + 1) == kBox)) return true;
  if ((table.Get(x - 1, y) == kBox)
   && (table.Get(x - 1, y - 1) == kBox) && (table.Get(x, y - 1) == kBox)) return true;
  if ((table.Get(x, y - 1) == kBox)
   && (table.Get(x + 1, y - 1) == kBox) && (table.Get(x + 1, y) == kBox)) return true;

  return false;
}
