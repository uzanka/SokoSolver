#include <map>
#include "GoalsHolder.h"

GoalsHolder::GoalsHolder() {
}

GoalsHolder::~GoalsHolder() {
}

void GoalsHolder::Clear() {
  goals_.clear();
  goal_xy_.clear();
}

void GoalsHolder::Add(const int x, const int y) {
  goals_.insert(std::make_pair(GetMapKey(x, y), 0));
  goal_xy_.push_back(std::tuple<int, int>(x, y));
}

bool GoalsHolder::Goal(const int x, const int y) const {
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
