#ifndef STALEMATE_FINDER_INCLUDED
#define STALEMATE_FINDER_INCLUDED

#include <map>
#include "Table.h"
#include "GoalsHolder.h"

class StalemateFinder {
public:
  StalemateFinder();
  virtual ~StalemateFinder();

  void Setup(const Table& table, const GoalsHolder& goals);
  bool Stalemate(const Table& table, const int x, const int y);

protected:
  void UpDown(const Table& table, const GoalsHolder& goals, const int x, const int y, const int cd, const int md);
  void RightLeft(const Table& table, const GoalsHolder& goals, const int x, const int y, const int cd, const int md);
  void AddV(const int x, const int y, const int count);
  void AddH(const int x, const int y, const int count);
  int Count(const Table& table, const int x, const int y, const int dx, const int dy);
  void print_map();

protected:
  int width_;
  int height_;
  std::map<int, int> v_;
  std::map<int, int> h_;
};

#endif  // STALEMATE_FINDER_INCLUDED
