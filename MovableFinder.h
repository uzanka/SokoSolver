#ifndef MOVABLE_FINDER_INCLUDED
#define MOVABLE_FINDER_INCLUDED

#include <vector>

namespace puzzle {

class MovableFinder {
public:
  MovableFinder(Table& table, const int width, const int height, const std::vector<std::tuple<int, int>>& goals);
  virtual ~MovableFinder();

  void ClearMovable();
  void DrawMovable(const int x, const int y);
  bool Unmovable();
  bool Pushable(std::vector<std::tuple<int, int>>& positions);

private:
  void DrawMovableRecursive(const int x, const int y);
  bool Goal(const int x, const int y);

public:
  int   width_;
  int   height_;
  Table table_;
  std::vector<std::tuple<int, int>> goals_;
};

}  // puzzle

#endif  // MOVABLE_FINDER_INCLUDED
