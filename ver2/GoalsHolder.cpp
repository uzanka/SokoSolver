#include <map>
#include "GoalsHolder.h"

GoalsHolder::GoalsHolder() {
  width_ = 0;
  height_ = 0;
}

GoalsHolder::~GoalsHolder() {
}

void GoalsHolder::Clear() {
  goals_.clear();
  goal_xy_.clear();
  width_ = 0;
  height_ = 0;
}

void GoalsHolder::Size(const int width, const int height) {
  width_ = width;
  height_ = height;
}

void GoalsHolder::Add(const int x, const int y) {
  goals_.insert(std::make_pair(GetMapKey(x, y), 0));
  goal_xy_.push_back(std::tuple<int, int>(x, y));
}

bool GoalsHolder::Goal(const int x, const int y) const {
  if ((x < 0) || (y < 0)
   || (x >= width_) || (y >= height_)) {
    return false;
  }
  return goals_.find(GetMapKey(x, y)) != goals_.end();
}

bool GoalsHolder::Solved(const Table& table) const {
  for (auto& goal : goals_) {
    if (table.Get(goal.first % 256, goal.first / 256) != kBox) {
      return false;
    }
  }
  return true;
}

void GoalsHolder::GetGoals(std::vector<std::tuple<int, int>>& goal_xy) const {
  goal_xy = goal_xy_;
}

int GoalsHolder::GetMapKey(const int x, const int y) const {
  return y * 256 + x;
}
