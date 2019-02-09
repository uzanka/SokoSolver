#include "SokoSolver2.h"
#include "MovableFinder.h"

namespace puzzle {

#define POS(x, y) ((x) + (y) * width_)

MovableFinder::MovableFinder(Table& table, const int width, const int height, const std::vector<std::tuple<int, int>>& goals)
  : table_(table), width_(width), height_(height), goals_(goals) {
}

MovableFinder::~MovableFinder() {
}

void MovableFinder::ClearMovable() {
  for (int y = 1; y < height_ - 1; y++) {
    for (int x = 1; x < width_ - 1; x++) {
      if (table_[POS(x, y)] == '.') {
        table_[POS(x, y)] = ' ';
      }
    }
  }
}

void MovableFinder::DrawMovable(const int x, const int y) {
  DrawMovableRecursive(x, y);
}

void MovableFinder::DrawMovableRecursive(const int x, const int y) {
  table_[POS(x, y)] = '.';
  if (table_[POS(x + 1, y)] == ' ') DrawMovableRecursive(x + 1, y);
  if (table_[POS(x - 1, y)] == ' ') DrawMovableRecursive(x - 1, y);
  if (table_[POS(x, y + 1)] == ' ') DrawMovableRecursive(x, y + 1);
  if (table_[POS(x, y - 1)] == ' ') DrawMovableRecursive(x, y - 1);
}

bool MovableFinder::Unmovable() {
  for (int y = 1; y < height_ - 1; y++) {
    for (int x = 1; x < width_ - 1; x++) {
      if (table_[POS(x, y)] == '$') {
        if (!Goal(x, y)) {
          // Box exists at unmovable corner.
          if ((table_[POS(x + 1, y)] == '#') && (table_[POS(x, y - 1)] == '#')) return true;
          if ((table_[POS(x + 1, y)] == '#') && (table_[POS(x, y + 1)] == '#')) return true;
          if ((table_[POS(x - 1, y)] == '#') && (table_[POS(x, y - 1)] == '#')) return true;
          if ((table_[POS(x - 1, y)] == '#') && (table_[POS(x, y + 1)] == '#')) return true;
        }
      }
    }
  }
  return false;
}

bool MovableFinder::Pushable(std::vector<std::tuple<int, int>>& positions) {
  for (int y = 1; y < height_ - 1; y++) {
    for (int x = 1; x < width_ - 1; x++) {
      if (table_[POS(x, y)] == '.') {
        if (((table_[POS(x + 1, y)] == '$') && ((table_[POS(x + 2, y)] == ' ') || (table_[POS(x + 2, y)] == '.')))
         || ((table_[POS(x - 1, y)] == '$') && ((table_[POS(x - 2, y)] == ' ') || (table_[POS(x - 2, y)] == '.')))
         || ((table_[POS(x, y + 1)] == '$') && ((table_[POS(x, y + 2)] == ' ') || (table_[POS(x, y + 2)] == '.')))
         || ((table_[POS(x, y - 1)] == '$') && ((table_[POS(x, y - 2)] == ' ') || (table_[POS(x, y - 2)] == '.')))) {
          positions.push_back(std::make_tuple(x, y));
        }
      }
    }
  }
  return false;
}

bool MovableFinder::Goal(const int x, const int y) {
  for (auto& goal : goals_) {
    if ((std::get<0>(goal) == x) && (std::get<1>(goal) == y)) {
      return true;
    }
  }
  return false;
}

}  // puzzle
