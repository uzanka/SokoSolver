#include "PushableFinder.h"

const int PushableFinder::kUp    = 0;
const int PushableFinder::kRight = 1;
const int PushableFinder::kDown  = 2;
const int PushableFinder::kLeft  = 3;

///////////////////////////////////////////////////////////////////////////////
PushableFinder::PushableFinder() {
}

///////////////////////////////////////////////////////////////////////////////
PushableFinder::~PushableFinder() {
}

///////////////////////////////////////////////////////////////////////////////
void PushableFinder::Pushable(Table& table, std::list<std::tuple<int, int, int>>& positions) {
  for (int y = 1; y < table.Height() - 1; y++) {
    for (int x = 1; x < table.Width() - 1; x++) {
      if (table.Get(x, y) == kPlayer) {
        if (Pushable(table.Get(x + 1, y), table.Get(x + 2, y))) {
          positions.push_back(std::make_tuple(x, y, kRight));
        }
        if (Pushable(table.Get(x - 1, y), table.Get(x - 2, y))) {
          positions.push_back(std::make_tuple(x, y, kLeft));
        }
        if (Pushable(table.Get(x, y + 1), table.Get(x, y + 2))) {
          positions.push_back(std::make_tuple(x, y, kDown));
        }
        if (Pushable(table.Get(x, y - 1), table.Get(x, y - 2))) {
          positions.push_back(std::make_tuple(x, y, kUp));
        }
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
void PushableFinder::Pushable2(Table& table, std::list<std::tuple<int, int, int>>& positions, Table& deadzone) {
  for (int y = 1; y < table.Height() - 1; y++) {
    for (int x = 1; x < table.Width() - 1; x++) {
      if (table.Get(x, y) == kPlayer) {
        if (Pushable(table.Get(x + 1, y), table.Get(x + 2, y))) {
          if (deadzone.Get(x + 2, y) != kWall) {
            positions.push_back(std::make_tuple(x, y, kRight));
          }
        }
        if (Pushable(table.Get(x - 1, y), table.Get(x - 2, y))) {
          if (deadzone.Get(x - 2, y) != kWall) {
            positions.push_back(std::make_tuple(x, y, kLeft));
          }
        }
        if (Pushable(table.Get(x, y + 1), table.Get(x, y + 2))) {
          if (deadzone.Get(x, y + 2) != kWall) {
            positions.push_back(std::make_tuple(x, y, kDown));
          }
        }
        if (Pushable(table.Get(x, y - 1), table.Get(x, y - 2))) {
          if (deadzone.Get(x, y - 2) != kWall) {
            positions.push_back(std::make_tuple(x, y, kUp));
          }
        }
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
bool PushableFinder::Pushable(const int value1, const int value2) {
  if ((value1 == kBox)
   && (value2 == kSpace || value2 == kPlayer)) {
    return true;
  }
  return false;
}
