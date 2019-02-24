#include "DeadzoneFinder.h"

///////////////////////////////////////////////////////////////////////////////
DeadzoneFinder::DeadzoneFinder() {
  Type11();
  Type12();
  Type21();
  Type22();
  Type23();
  Type24();
  Type31();
  Type32();
  Type33();
  Type34();
  Type41();
  Type42();
  Type51();
  Type61();
  Type71();
  Type81();
  Type91();
}

///////////////////////////////////////////////////////////////////////////////
DeadzoneFinder::~DeadzoneFinder() {
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Initialize(const Table& table, const GoalsHolder& goals, Table& deadzone) {
  deadzone_ = table;

  deadzone_.Replace(kBox, kSpace);

  std::vector<std::tuple<int, int>> goal_xy;
  goals.GetGoals(goal_xy);
  for (auto& xy : goal_xy) {
    deadzone_.Set(std::get<0>(xy), std::get<1>(xy), kBox);  // dummy
  }

  for (int y = 0; y < table.Height(); y++) {
    for (int x = 0; x < table.Width(); x++) {
      for (auto& pattern : patterns_) {
        bool flag = true;
        for (auto& position : pattern.positions_) {
          if ((x + std::get<0>(position) >= table.Width())
           || (y + std::get<1>(position) >= table.Height())) {
            flag = false;
            break;
          }
          if (table.Get(x + std::get<0>(position), y + std::get<1>(position)) != std::get<2>(position)) {
            flag = false;
            break;
          } else {
            if (goals.Goal(x + std::get<0>(position), y + std::get<1>(position))) {
              flag = false;
              break;
            }
          }
        }
        if (flag) {
          for (auto& position : pattern.positions_) {
            if (std::get<2>(position) == kSpace) {
              deadzone_.Set(x + std::get<0>(position), y + std::get<1>(position), kWall);
            }
          }
        }
      }
    }
  }
  deadzone = deadzone_;
}

///////////////////////////////////////////////////////////////////////////////
bool DeadzoneFinder::Deadzone(const int x, const int y) {
  if (deadzone_.Get(x, y) == kWall) {
    return true;
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type11() {
  // #x  ?#  #?  x#
  // ?#  #x  x#  #?

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 0, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type12() {
  // #x#  ?#  ?#?  #?
  // ?#?  #x  #x#  x#
  //      ?#       #?

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type21() {
  // #xx#  ?#  ?##?  #?
  // ?##?  #x  #xx#  x#
  //       #x        x#
  //       ?#        #?

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(3, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(2, 0, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 3, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(3, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 3, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 2, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type22() {
  // #x#  ?##  ?#?  ##?
  // #x#  #xx  #x#  xx#
  // ?#?  ?##  #x#  ##?

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(2, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(2, 1, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 2, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(1, 2, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type23() {
  // #x?  ?##  ?#?  ?#?
  // #x#  #xx  #x#  xx#
  // ?#?  ?#?  ?x#  ##?

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(2, 1, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 2, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(1, 2, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type24() {
  // ?x#  ?#?  ?#?  ##?
  // #x#  #xx  #x#  xx#
  // ?#?  ?##  #x?  ?#?

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(2, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(2, 1, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(1, 2, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type31() {
  // #xxx#  ?#  ?###?  #?
  // ?###?  #x  #xxx#  x#
  //        #x         x#
  //        #x         x#
  //        ?#         #?

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(4, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(3, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(2, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(3, 0, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 3, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 4, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 3, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(3, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(4, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(3, 1, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 3, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 4, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 2, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 3, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type32() {
  // #x#  ?###  ?#?  ###?
  // #x#  #xxx  #x#  xxx#
  // #x#  ?###  #x#  ###?
  // ?#?        #x#

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 2, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 3, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern1.Add(std::tuple<int, int, int>(1, 2, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(3, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(2, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(3, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(2, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(3, 1, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 2, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 3, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 3, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(1, 2, kSpace));
  pattern3.Add(std::tuple<int, int, int>(1, 3, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(3, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(2, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(2, 1, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type33() {
  // #xx#  ??#  ?#??  ##?
  // ?#x#  ?#x  #x#?  xx#
  // ??#?  #xx  #xx#  x#?
  //       ?##        #??

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(3, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(3, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 2, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(2, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 3, kWall));
  pattern2.Add(std::tuple<int, int, int>(2, 3, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kSpace));
  pattern2.Add(std::tuple<int, int, int>(2, 2, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern3.Add(std::tuple<int, int, int>(3, 2, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(1, 2, kSpace));
  pattern3.Add(std::tuple<int, int, int>(2, 2, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 3, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 2, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type34() {
  // #xx#  #??  ?##  ?##
  // #x#?  x#?  #xx  #xx
  // ?#??  xx#  ?#x  ?#x
  //       ##?  ??#  ??#

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(3, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(2, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(2, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 3, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 3, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(0, 2, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 3, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(2, 2, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(2, 3, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(2, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(2, 2, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type41() {
  // #xxxx#  ?#  ?####?  #?
  // ?####?  #x  #xxxx#  x#
  //         #x          x#
  //         #x          x#
  //         #x          x#
  //         ?#          #?

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(5, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(3, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(4, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(2, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(3, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(4, 0, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 3, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 4, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 5, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 3, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 4, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(3, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(4, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(5, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(3, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(4, 1, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 3, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 4, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 5, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 2, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 3, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 4, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type42() {
  // #xxx#  ??#  ??#??  #??
  // ?#x#?  ?#x  ?#x#?  x#?
  // ??#??  #xx  #xxx#  xx#
  //        ?#x         x#?
  //        ??#         #??

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(4, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(3, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 2, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(2, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(3, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 3, kWall));
  pattern2.Add(std::tuple<int, int, int>(2, 4, kWall));
  pattern2.Add(std::tuple<int, int, int>(2, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kSpace));
  pattern2.Add(std::tuple<int, int, int>(2, 2, kSpace));
  pattern2.Add(std::tuple<int, int, int>(2, 3, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(3, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern3.Add(std::tuple<int, int, int>(4, 2, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(1, 2, kSpace));
  pattern3.Add(std::tuple<int, int, int>(2, 2, kSpace));
  pattern3.Add(std::tuple<int, int, int>(3, 2, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(2, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 3, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 4, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 2, kSpace));
  pattern4.Add(std::tuple<int, int, int>(1, 2, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 3, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type51() {
  // #xxxxx#  ?#  ?#####?  #?
  // ?#####?  #x  #xxxxx#  x#
  //          #x           x#
  //          #x           x#
  //          #x           x#
  //          #x           x#
  //          ?#           #?

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(6, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(3, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(4, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(5, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(2, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(3, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(4, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(5, 0, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 3, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 4, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 5, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 6, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 3, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 4, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 5, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(3, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(4, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(5, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(6, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(3, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(4, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(5, 1, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 3, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 4, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 5, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 6, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 2, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 3, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 4, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 5, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type61() {
  // #xxxxxx#  ?#  ?######?  #?
  // ?######?  #x  #xxxxxx#  x#
  //           #x            x#
  //           #x            x#
  //           #x            x#
  //           #x            x#
  //           #x            x#
  //           ?#            #?

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(7, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(3, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(4, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(5, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(6, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(2, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(3, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(4, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(5, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(6, 0, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 3, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 4, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 5, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 6, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 7, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 3, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 4, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 5, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 6, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(3, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(4, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(5, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(6, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(7, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(3, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(4, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(5, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(6, 1, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 3, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 4, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 5, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 6, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 7, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 2, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 3, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 4, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 5, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 6, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type71() {
  // #xxxxxxx#  ?#  ?#######?  #?
  // ?#######?  #x  #xxxxxxx#  x#
  //            #x             x#
  //            #x             x#
  //            #x             x#
  //            #x             x#
  //            #x             x#
  //            #x             x#
  //            ?#             #?

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(8, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(3, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(4, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(5, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(6, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(7, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(2, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(3, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(4, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(5, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(6, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(7, 0, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 3, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 4, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 5, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 6, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 7, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 8, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 3, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 4, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 5, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 6, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 7, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(3, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(4, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(5, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(6, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(7, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(8, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(3, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(4, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(5, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(6, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(7, 1, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 3, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 4, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 5, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 6, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 7, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 8, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 2, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 3, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 4, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 5, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 6, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 7, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type81() {
  // #xxxxxxxx#  ?#  ?########?  #?
  // ?########?  #x  #xxxxxxxx#  x#
  //             #x              x#
  //             #x              x#
  //             #x              x#
  //             #x              x#
  //             #x              x#
  //             #x              x#
  //             #x              x#
  //             ?#              #?

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(9, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(3, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(4, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(5, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(6, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(7, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(8, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(2, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(3, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(4, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(5, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(6, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(7, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(8, 0, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 3, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 4, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 5, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 6, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 7, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 8, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 9, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 3, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 4, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 5, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 6, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 7, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 8, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(3, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(4, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(5, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(6, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(7, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(8, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(9, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(3, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(4, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(5, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(6, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(7, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(8, 1, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 3, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 4, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 5, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 6, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 7, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 8, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 9, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 2, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 3, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 4, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 5, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 6, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 7, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 8, kSpace));
  Add(pattern4);
}

///////////////////////////////////////////////////////////////////////////////
void DeadzoneFinder::Type91() {
  // #xxxxxxxxx#  ?#  ?#########?  #?
  // ?#########?  #x  #xxxxxxxxx#  x#
  //              #x               x#
  //              #x               x#
  //              #x               x#
  //              #x               x#
  //              #x               x#
  //              #x               x#
  //              #x               x#
  //              #x               x#
  //              ?#               #?

  Pattern pattern1;
  pattern1.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(10, 0, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(2, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(3, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(4, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(5, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(6, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(7, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(8, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(9, 1, kWall));
  pattern1.Add(std::tuple<int, int, int>(1, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(2, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(3, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(4, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(5, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(6, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(7, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(8, 0, kSpace));
  pattern1.Add(std::tuple<int, int, int>(9, 0, kSpace));
  Add(pattern1);

  Pattern pattern2;
  pattern2.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 2, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 3, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 4, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 5, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 6, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 7, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 8, kWall));
  pattern2.Add(std::tuple<int, int, int>(0, 9, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 10, kWall));
  pattern2.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 2, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 3, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 4, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 5, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 6, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 7, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 8, kSpace));
  pattern2.Add(std::tuple<int, int, int>(1, 9, kSpace));
  Add(pattern2);

  Pattern pattern3;
  pattern3.Add(std::tuple<int, int, int>(1, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(2, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(3, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(4, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(5, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(6, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(7, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(8, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(9, 0, kWall));
  pattern3.Add(std::tuple<int, int, int>(0, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(10, 1, kWall));
  pattern3.Add(std::tuple<int, int, int>(1, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(2, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(3, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(4, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(5, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(6, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(7, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(8, 1, kSpace));
  pattern3.Add(std::tuple<int, int, int>(9, 1, kSpace));
  Add(pattern3);

  Pattern pattern4;
  pattern4.Add(std::tuple<int, int, int>(0, 0, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 1, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 2, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 3, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 4, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 5, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 6, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 7, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 8, kWall));
  pattern4.Add(std::tuple<int, int, int>(1, 9, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 10, kWall));
  pattern4.Add(std::tuple<int, int, int>(0, 1, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 2, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 3, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 4, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 5, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 6, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 7, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 8, kSpace));
  pattern4.Add(std::tuple<int, int, int>(0, 9, kSpace));
  Add(pattern4);
}
