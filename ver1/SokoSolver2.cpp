#include "SokoSolver2.h"
#include "MovableFinder.h"

namespace std {

///////////////////////////////////////////////////////////////////////////////
template<>
class hash<puzzle::Table> {
public:
  std::size_t operator()(const puzzle::Table& p) const {
    std::size_t idx = 32452843;
    for (std::size_t i = 0; i < p.size(); i++) {
      idx = idx * 37 + static_cast<uint8_t>(p[i]);
    }
    return idx;
  }
};

}  // std

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
SokoSolver2::SokoSolver2(const std::string board, const bool verbose)
  : width_(0), height_(0), px_(0), py_(0),
    looped_count_(0), max_opened_count_(0), visited_count_(0), elapsed_(0), verbose_(verbose) {
  dirs_ = {
    std::make_tuple( 0, -1, 'u', 'U'),
    std::make_tuple( 1,  0, 'r', 'R'),
    std::make_tuple( 0,  1, 'd', 'D'),
    std::make_tuple(-1,  0, 'l', 'L')
  };

  map_translate_chars_ = { {' ',' '}, {'.',' '}, {'@',' '}, {'+',' '}, {'#','#'}, {'$','$'}, {'*','$'} };

  SetupBoard(board);
}

///////////////////////////////////////////////////////////////////////////////
SokoSolver2::~SokoSolver2() {
}

///////////////////////////////////////////////////////////////////////////////
std::string SokoSolver2::Solve() {
  solution_ = "";
  looped_count_ = 0;
  max_opened_count_ = 0;
  visited_count_ = 0;
  elapsed_ = 0;

  std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
  solution_ = SolveMain();
  std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
  elapsed_ = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  return solution_;
}

///////////////////////////////////////////////////////////////////////////////
std::string SokoSolver2::SolveMain() {
  std::unordered_set<Table, std::hash<Table>> visited;
  std::queue<std::tuple<Table, std::string>> open;

  MovableFinder init_finder(initial_map_, width_, height_, goals_);
  init_finder.DrawMovable(px_, py_);
  //print_map(init_finder.table_);

  visited.insert(init_finder.table_);
  open.push(std::make_tuple(init_finder.table_, ""));

  while (open.size() > 0) {
    max_opened_count_ = std::max(max_opened_count_, open.size());
    ++looped_count_;
    
    Table current_map = std::get<0>(open.front());
    std::string current_solution = std::get<1>(open.front());
    open.pop();

    if (verbose_) {
      if (looped_count_ % 100000 == 0) {
        std::cout << std::to_string(looped_count_) + ": open=" + std::to_string(open.size()) + " / " + std::to_string(max_opened_count_) + " visited=" + std::to_string(visited.size()) << std::endl;
        //print_map(current_map);
      }
    }

    //print_map(current_map);
    MovableFinder current_finder(current_map, width_, height_, goals_);
    std::vector<std::tuple<int, int>> positions;
    current_finder.Pushable(positions);
    current_finder.ClearMovable();

    for (auto& xy : positions) {
      int x = std::get<0>(xy);
      int y = std::get<1>(xy);

      for (int i = 0; i < 4; ++i) {
        Table temp = current_finder.table_;
        int dx = std::get<0>(dirs_[i]);
        int dy = std::get<1>(dirs_[i]);

        if (temp[GetArrayIndex(x + dx, y + dy)] == '$') {
          if (Push(x, y, dx, dy, temp)) {
            if (IsSolved(temp)) {
              visited_count_ = visited.size();
              std::string sol = "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::get<3>(dirs_[i]) + ") ";
              return current_solution + sol;
            }
            MovableFinder next_finder(temp, width_, height_, goals_);
            next_finder.DrawMovable(x + dx, y + dy);
            if (!next_finder.Unmovable()) {
              if (visited.find(next_finder.table_) == visited.end()) {
                std::string sol = "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::get<3>(dirs_[i]) + ") ";
                open.push(std::make_tuple(next_finder.table_, current_solution + sol));
                visited.insert(next_finder.table_);
              }
            }
          }
        }
      }
    }
  }

  visited_count_ = visited.size();
  return "No solution.";
}

///////////////////////////////////////////////////////////////////////////////
void SokoSolver2::SetupBoard(const std::string board) {
  // Clear work values.
  goals_.clear();
  initial_map_ = "";
  width_ = 0;
  height_ = 0;
  px_ = 0;
  py_ = 0;

  std::vector<std::string> lines = Split(board, '\n');

  // Get map size.
  width_ = 0;
  for (auto& row : lines) {
    width_ = std::max(width_, static_cast<int>(row.size()));
  }
  height_ = static_cast<int>(lines.size());

  for (std::size_t y = 0; y < lines.size(); y++) {
    for (std::size_t x = 0; x < width_; x++) {
      char ch = (x < lines[y].size()) ? lines[y][x] : ' ';
      initial_map_ += map_translate_chars_[ch];
      if (ch == '@' || ch == '+') {
        px_ = static_cast<int>(x);
        py_ = static_cast<int>(y);
      }
      if (ch == '.' || ch == '*' || ch == '+') {
        goals_.push_back(std::make_tuple(static_cast<int>(x), static_cast<int>(y)));
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
bool SokoSolver2::Push(const int x, const int y, const int dx, const int dy, Table& data) {
  if (data[GetArrayIndex(x + 2 * dx, y + 2 * dy)] != ' ') {
    return false;
  }

  data[GetArrayIndex(x + dx, y + dy)] = ' ';
  data[GetArrayIndex(x + 2 * dx, y + 2 * dy)] = '$';
  return true;
}

///////////////////////////////////////////////////////////////////////////////
bool SokoSolver2::IsSolved(const Table& data) {
  for (auto& goal : goals_) {
    if (data[GetArrayIndex(std::get<0>(goal), std::get<1>(goal))] != '$') {
      return false;
    }
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////
int SokoSolver2::GetArrayIndex(const int x, const int y) const {
  return y * width_ + x;
}

///////////////////////////////////////////////////////////////////////////////
std::vector<std::string> SokoSolver2::Split(const std::string& str, const char delim) {
  std::vector<std::string> elems;
  std::stringstream ss(str);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

///////////////////////////////////////////////////////////////////////////////
void SokoSolver2::print_map(const Table& data) {
  for (int y = 0; y < height_; y++) {
    std::cout << data.substr(y * width_, width_) << std::endl;
  }
  //std::cout << std::to_string(x) + "," + std::to_string(y) << std::endl;
  std::cout << std::endl;
}

}  // puzzle
