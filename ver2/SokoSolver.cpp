#include "SokoSolver.h"
#include "Table.h"
#include "MovableDrawer.h"
#include "PushableFinder.h"
#include "UnmovableFinder.h"

///////////////////////////////////////////////////////////////////////////////
SokoSolver::SokoSolver(const std::vector<std::string>& board, const bool verbose, const int timeout)
  : width_(0), height_(0), px_(0), py_(0),
    looped_count_(0), max_opened_count_(0), visited_count_(0), verbose_(verbose), timeout_(timeout) {

  dirs_ = {
    std::make_tuple( 0, -1, 'u', 'U'),
    std::make_tuple( 1,  0, 'r', 'R'),
    std::make_tuple( 0,  1, 'd', 'D'),
    std::make_tuple(-1,  0, 'l', 'L')
  };

  SetupBoard(board);
}

///////////////////////////////////////////////////////////////////////////////
SokoSolver::~SokoSolver() {
}

///////////////////////////////////////////////////////////////////////////////
std::string SokoSolver::Solve() {
  solution_ = "";
  looped_count_ = 0;
  max_opened_count_ = 0;
  visited_count_ = 0;

  start_ = std::chrono::system_clock::now();

  std::unordered_set<Table, std::hash<Table>> visited;
  std::queue<std::tuple<Table, std::string>> open;

  Table initial_table(initial_map_);
  MovableDrawer::DrawRecursive(initial_table, px_, py_);
  //print_map(initial_table);

  visited.insert(initial_table);
  open.push(std::make_tuple(initial_table, ""));

  while (open.size() > 0) {
    max_opened_count_ = std::max(max_opened_count_, open.size());
    ++looped_count_;

    Table current_map(std::get<0>(open.front()));
    std::string current_solution = std::get<1>(open.front());
    open.pop();

    if (looped_count_ % 100000 == 0) {
      if (verbose_) {
        std::cout << std::to_string(looped_count_) + ": open=" + std::to_string(open.size()) + " / " + std::to_string(max_opened_count_) + " visited=" + std::to_string(visited.size()) << std::endl;
        //print_map(current_map);
      }
    }
    if (looped_count_ % 100 == 0) {
      if (timeout_ > 0) {
        std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
        uint64_t elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start_).count();
        if (elapsed / 1000 >= timeout_) {
          visited_count_ = visited.size();
          return "No solution (timeout).";
        }
      }
    }

    //print_map(current_map);
    std::list<std::tuple<int, int, int>> positions;
    //PushableFinder::Pushable(current_map, positions);
    PushableFinder::Pushable2(current_map, positions, deadzone_);
    current_map.Replace(kPlayer, kSpace);
    //print_map(current_map);

    for (auto& xyv : positions) {
      int x = std::get<0>(xyv);
      int y = std::get<1>(xyv);
      int v = std::get<2>(xyv);

      Table temp(current_map);
      int dx = std::get<0>(dirs_[v]);
      int dy = std::get<1>(dirs_[v]);

      if (temp.Get(x + dx, y + dy) == kBox) {
        if (Push(temp, x, y, dx, dy)) {
          //print_map(temp);
          if (goals_.Solved(temp)) {
            visited_count_ = visited.size();
            std::string sol = "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::get<3>(dirs_[v]) + ") ";
            return current_solution + sol;
          }
          if (deadzone_.Get(x + dx * 2, y + dy * 2) != kWall) {
            if (!unmovable_.Unmovable(temp, goals_, x + dx * 2, y + dy * 2)) {
              Table next_table(temp);
              MovableDrawer::DrawRecursive(next_table, x + dx, y + dy);
              //print_map(next_table);
              if (visited.find(next_table) == visited.end()) {
                std::string sol = "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::get<3>(dirs_[v]) + ") ";
                open.push(std::make_tuple(next_table, current_solution + sol));
                visited.insert(next_table);
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
void SokoSolver::SetupBoard(const std::vector<std::string>& board) {
  // Get map size.
  height_ = (int)board.size();
  width_ = 0;
  for (auto& row : board) {
    width_ = std::max(width_, (int)row.size());
  }

  std::map<char, int> map_translate_chars = {
    {' ', kSpace},
    {'.', kSpace},
    {'@', kSpace},
    {'+', kSpace},
    {'#', kWall},
    {'$', kBox},
    {'*', kBox}
  };

  goals_.Clear();
  initial_map_ = Table(width_, height_);
  px_ = 0;
  py_ = 0;
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      char ch = (x < (int)board[y].size()) ? board[y][x] : ' ';
      initial_map_.Set(x, y, map_translate_chars[ch]);
      if (ch == '@' || ch == '+') {
        px_ = x;
        py_ = y;
      }
      if (ch == '.' || ch == '*' || ch == '+') {
        goals_.Add(x, y);
      }
    }
  }

  DeadzoneFinder deadzone;
  deadzone.Initialize(initial_map_, goals_, deadzone_);
  //print_map(deadzone_);
}

///////////////////////////////////////////////////////////////////////////////
bool SokoSolver::Push(Table& table, const int x, const int y, const int dx, const int dy) {
  if (table.Get(x + 2 * dx, y + 2 * dy) != kSpace) {
    return false;
  }

  table.Set(x + dx, y + dy, kSpace);
  table.Set(x + 2 * dx, y + 2 * dy, kBox);
  return true;
}

///////////////////////////////////////////////////////////////////////////////
void SokoSolver::print_map(const Table& table) {
  for (int y = 0; y < table.Height(); y++) {
    std::string buffer;
    for (int x = 0; x < table.Width(); x++) {
      int value = table.Get(x, y);
      if (value == kSpace) {
        buffer += ' ';
      } else if (value == kBox) {
        buffer += '$';
      } else if (value == kPlayer) {
        buffer += '@';
      } else if (value == kWall) {
        buffer += '#';
      } else {
        buffer += '?';
      }
    }
    std::cout << buffer << std::endl;
  }
  std::cout << std::endl;
}
