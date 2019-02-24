#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Table.h"
#include "GoalsHolder.h"

class BoardCreator {
public:
  BoardCreator() {
  }

  virtual ~BoardCreator() {
  }

  static void Create(const std::vector<std::string>& lines, Table& table) {
    GoalsHolder goals;
    std::tuple<int, int> player;
    Create(lines, table, goals, player);
  }

  static void Create(const std::vector<std::string>& lines, Table& table, GoalsHolder& goals) {
    std::tuple<int, int> player;
    Create(lines, table, goals, player);
  }

  static void Create(const std::vector<std::string>& lines, Table& table, GoalsHolder& goals, std::tuple<int, int>& player) {
    std::map<char, int> map_translate_chars = {
      {' ', kSpace},
      {'.', kSpace},
      {'@', kSpace},
      {'+', kSpace},
      {'#', kWall},
      {'$', kBox},
      {'*', kBox},
      {'C', kBox}
    };

    int height = (int)lines.size();
    int width = 0;
    for (auto& row : lines) {
      width = std::max(width, (int)row.size());
    }
    table = Table(width, height, kSpace);
    goals.Clear();
    goals.Size(width, height);
    player = std::tuple<int, int>(0, 0);

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        char ch = (x < (int)lines[y].size()) ? lines[y][x] : ' ';
        table.Set(x, y, map_translate_chars[ch]);
        if (ch == '@' || ch == '+') {
          player = std::tuple<int, int>(x, y);
        }
        if (ch == '.' || ch == '*' || ch == '+') {
          goals.Add(x, y);
        }
      }
    }
  }

  static std::vector<std::string>& ConvertBoard(std::vector<std::string>& lines) {
    for (auto& data : lines) {
      std::replace(data.begin(), data.end(), '?', '#');
    }
    return lines;
  }
};
