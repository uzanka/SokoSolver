#include <iostream>
#include <string>
#include "StalemateFinder.h"

///////////////////////////////////////////////////////////////////////////////
StalemateFinder::StalemateFinder() {
}

///////////////////////////////////////////////////////////////////////////////
StalemateFinder::~StalemateFinder() {
}

///////////////////////////////////////////////////////////////////////////////
bool StalemateFinder::Stalemate(const Table& table, const int x, const int y) {
  auto itrv = v_.find(x + y * width_);
  if (itrv != v_.end()) {
    if (Count(table, x, y, 0, 1) > itrv->second) {
      return true;
    }
  }

  auto itrh = h_.find(x + y * width_);
  if (itrh != h_.end()) {
    if (Count(table, x, y, 1, 0) > itrh->second) {
      return true;
    }
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////
int StalemateFinder::Count(const Table& table, const int x, const int y, const int dx, const int dy) {
  int count = 0;
  int cx = x;
  int cy = y;
  while(table.Get(cx, cy) != kWall) {
    if (table.Get(cx, cy) == kBox) ++count;
    cx += dx;
    cy += dy;
  }
  cx = x - dx;
  cy = y - dy;
  while(table.Get(cx, cy) != kWall) {
    if (table.Get(cx, cy) == kBox) ++count;
    cx -= dx;
    cy -= dy;
  }
  return count;
}

///////////////////////////////////////////////////////////////////////////////
void StalemateFinder::Setup(const Table& table, const GoalsHolder& goals) {
  width_  = table.Width();
  height_ = table.Height();

  for (int y = 1; y < height_ - 1; y++) {
    for (int x = 1; x < width_ - 1; x++) {
      //C#
      //#?
      if ((table.Get(x + 1, y) == kWall) && (table.Get(x, y + 1) == kWall)) {
        // Up(R)
        UpDown(table, goals, x, y, 1, -1);
        // Left(D)
        RightLeft(table, goals, x, y, 1, -1);
      }

      //#C
      //?#
      if ((table.Get(x - 1, y) == kWall) && (table.Get(x, y + 1) == kWall)) {
        // Up(L)
        UpDown(table, goals, x, y, -1, -1);
        // Right(D)
        RightLeft(table, goals, x, y, 1, 1);
      }

      //?#
      //#C
      if ((table.Get(x - 1, y) == kWall) && (table.Get(x, y - 1) == kWall)) {
        // Down(L)
        UpDown(table, goals, x, y, -1, 1);
        // Right(U)
        RightLeft(table, goals, x, y, -1, 1);
      }

      //#?
      //C#
      if ((table.Get(x + 1, y) == kWall) && (table.Get(x, y - 1) == kWall)) {
        // Down(R)
        UpDown(table, goals, x, y, 1, 1);
        // Left(U)
        RightLeft(table, goals, x, y, -1, -1);
      }
    }
  }

  //print_map();
}

///////////////////////////////////////////////////////////////////////////////
void StalemateFinder::UpDown(const Table& table, const GoalsHolder& goals, const int x, const int y, const int cd, const int md) {
  int dy = y;
  int count = 0;
  while(table.Get(x, dy) != kWall) {
    if (table.Get(x + cd, dy) != kWall) return;
    if (goals.Goal(x, dy)) ++count;
    dy += md;
  }
  if (count == 0) return;

  dy = y;
  while(table.Get(x, dy) != kWall) {
    AddV(x, dy, count);
    dy += md;
  }
}

///////////////////////////////////////////////////////////////////////////////
void StalemateFinder::RightLeft(const Table& table, const GoalsHolder& goals, const int x, const int y, const int cd, const int md) {
  int dx = x;
  int count = 0;
  while(table.Get(dx, y) != kWall) {
    if (table.Get(dx, y + cd) != kWall) return;
    if (goals.Goal(dx, y)) ++count;
    dx += md;
  }
  if (count == 0) return;

  dx = x;
  while(table.Get(dx, y) != kWall) {
    AddH(dx, y, count);
    dx += md;
  }
}

///////////////////////////////////////////////////////////////////////////////
void StalemateFinder::AddV(const int x, const int y, const int count) {
  v_.insert(std::make_pair(x + y * width_, count));
}

///////////////////////////////////////////////////////////////////////////////
void StalemateFinder::AddH(const int x, const int y, const int count) {
  h_.insert(std::make_pair(x + y * width_, count));
}

///////////////////////////////////////////////////////////////////////////////
void StalemateFinder::print_map() {
  for (auto& itrv : v_) {
    int x = itrv.first % width_;
    int y = itrv.first / width_;
    std::string msg;
    msg = "V(" + std::to_string(x) + "," + std::to_string(y) + ") = " + std::to_string(itrv.second);
    std::cout << msg << std::endl;
  }

  for (auto& itrh : h_) {
    int x = itrh.first % width_;
    int y = itrh.first / width_;
    std::string msg;
    msg = "H(" + std::to_string(x) + "," + std::to_string(y) + ") = " + std::to_string(itrh.second);
    std::cout << msg << std::endl;
  }
}
