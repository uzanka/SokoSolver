#include <iostream>
#include "UnmovableFinder.h"
#include "BoardCreator.h"
#include "CppUTest/CommandLineTestRunner.h"

///////////////////////////////////////////////////////////////////////////////
TEST_GROUP(UnmovableFinder2) {
  TEST_SETUP() {
  }

  TEST_TEARDOWN() {
  }
};

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check11) {
  try {
    std::vector<std::string> board = {
    // 0123456789012345
      "????????????????",
      "?#???$#???#??#$?",
      "?$#??#???#$???#?",
      "????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(BoardCreator::ConvertBoard(board), table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check11(table, 1, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 1, 2));

    CHECK_EQUAL(true, target.Check11(table, 5, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 5, 1));

    CHECK_EQUAL(true, target.Check11(table, 10, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 10, 2));

    CHECK_EQUAL(true, target.Check11(table, 14, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 14, 1));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check21) {
  try {
    std::vector<std::string> board = {
    // 0123456789012345
      "????????????????",
      "?C#??$C??#$??##?",
      "?$#??##??#C??C$?",
      "????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check21(table, 1, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 1, 1));

    CHECK_EQUAL(true, target.Check21(table, 6, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 6, 1));

    CHECK_EQUAL(true, target.Check21(table, 10, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 10, 2));

    CHECK_EQUAL(true, target.Check21(table, 13, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 13, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
    // 0123456789012345
      "????????????????",
      "?$#??C$??#C??##?",
      "?C#??##??#$??$C?",
      "????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check21(table, 1, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 1, 2));

    CHECK_EQUAL(true, target.Check21(table, 5, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 5, 1));

    CHECK_EQUAL(true, target.Check21(table, 10, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 10, 1));

    CHECK_EQUAL(true, target.Check21(table, 14, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 14, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check22) {
  std::vector<std::string> board = {
    // 012345678901234567
      "??????????????????",
      "??C#??#????$#??#??",
      "?#$???$C??#C???C$?",
      "???????#????????#?",
      "??????????????????"
  };
  Table table;
  GoalsHolder goals;
  BoardCreator::Create(board, table, goals);
  UnmovableFinder target;

  try {
    CHECK_EQUAL(true, target.Check22(table, 2, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 1));

    CHECK_EQUAL(true, target.Check22(table, 7, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 7, 2));

    CHECK_EQUAL(true, target.Check22(table, 11, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 11, 2));

    CHECK_EQUAL(true, target.Check22(table, 15, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 15, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check23) {
  try {
    std::vector<std::string> board = {
    // 01234567890123456789
      "????????????????????",
      "??##??##????$#??#C??",
      "?# C??$ #??C #??# $?",
      "?#$????C#??##????##?",
      "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check23(table, goals, 3, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 3, 2));

    CHECK_EQUAL(true, target.Check23(table, goals, 7, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 7, 3));

    CHECK_EQUAL(true, target.Check23(table, goals, 11, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 11, 2));

    CHECK_EQUAL(true, target.Check23(table, goals, 17, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 17, 1));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
    // 01234567890123456789
      "????????????????????",
      "??##??##????C#??#$??",
      "?# $??C #??$ #??# C?",
      "?#C????$#??##????##?",
      "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check23(table, goals, 2, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 3));

    CHECK_EQUAL(true, target.Check23(table, goals, 6, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 6, 2));

    CHECK_EQUAL(true, target.Check23(table, goals, 12, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 1));

    CHECK_EQUAL(true, target.Check23(table, goals, 18, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 18, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check24) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?#C????$#???#????#??",
        "?$ #??# C??# $??C #?",
        "??#????#????C#??#$??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check24(table, goals, 2, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 1));

    CHECK_EQUAL(true, target.Check24(table, goals, 8, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 2));

    CHECK_EQUAL(true, target.Check24(table, goals, 12, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 3));

    CHECK_EQUAL(true, target.Check24(table, goals, 16, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 16, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "??C#???#????#???#$??",
        "?# $??# C??$ #??C #?",
        "??#????$#??#C????#??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check24(table, goals, 2, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 1));

    CHECK_EQUAL(true, target.Check24(table, goals, 8, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 2));

    CHECK_EQUAL(true, target.Check24(table, goals, 12, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 3));

    CHECK_EQUAL(true, target.Check24(table, goals, 16, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 16, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check25) {
  try {
    std::vector<std::string> board = {
    // 01234567890123456789
      "????????????????????",
      "?$C????#$???#????#??",
      "?# #??# C??# #??C #?",
      "??#????#????C$??$#??",
      "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check25(table, goals, 2, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 1));

    CHECK_EQUAL(true, target.Check25(table, goals, 8, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 2));

    CHECK_EQUAL(true, target.Check25(table, goals, 12, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 3));

    CHECK_EQUAL(true, target.Check25(table, goals, 16, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 16, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
    // 01234567890123456789
      "????????????????????",
      "??C$???#????#???$#??",
      "?# #??# C??# #??C #?",
      "??#????#$??$C????#??",
      "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check25(table, goals, 2, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 1));

    CHECK_EQUAL(true, target.Check25(table, goals, 8, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 2));

    CHECK_EQUAL(true, target.Check25(table, goals, 12, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 3));

    CHECK_EQUAL(true, target.Check25(table, goals, 16, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 16, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check26) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?C$????#C???#????#??",
        "?# #??# $??# #??$ #?",
        "??#????#????$C??C#??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check26(table, goals, 1, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 1, 1));

    CHECK_EQUAL(true, target.Check26(table, goals, 8, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 1));

    CHECK_EQUAL(true, target.Check26(table, goals, 13, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 13, 3));

    CHECK_EQUAL(true, target.Check26(table, goals, 16, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 16, 3));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "??$C???#????#???C#??",
        "?# #??# $??# #??$ #?",
        "??#????#C??C$????#??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check26(table, goals, 3, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 3, 1));

    CHECK_EQUAL(true, target.Check26(table, goals, 8, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 3));

    CHECK_EQUAL(true, target.Check26(table, goals, 11, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 11, 3));

    CHECK_EQUAL(true, target.Check26(table, goals, 16, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 16, 1));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check27) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?#C???###???$#???#??",
        "?# #??$ C??# #??C $?",
        "?#$????#????C#??###?",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check27(table, goals, 2, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 1));

    CHECK_EQUAL(true, target.Check27(table, goals, 8, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 2));

    CHECK_EQUAL(true, target.Check27(table, goals, 12, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 3));

    CHECK_EQUAL(true, target.Check27(table, goals, 16, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 16, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?#$???###???C#???#??",
        "?# #??C $??# #??$ C?",
        "?#C????#????$#??###?",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check27(table, goals, 2, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 3));

    CHECK_EQUAL(true, target.Check27(table, goals, 6, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 6, 2));

    CHECK_EQUAL(true, target.Check27(table, goals, 12, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 1));

    CHECK_EQUAL(true, target.Check27(table, goals, 18, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 18, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check28) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?#C????##??#$????##?",
        "?# #??$ C??# #??C $?",
        "??$#??##????C#??##??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check28(table, goals, 2, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 1));

    CHECK_EQUAL(true, target.Check28(table, goals, 8, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 2));

    CHECK_EQUAL(true, target.Check28(table, goals, 12, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 3));

    CHECK_EQUAL(true, target.Check28(table, goals, 16, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 16, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check31) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????",
        "?C#??$C??$$??#$?",
        "?$$??$#??#C??C$?",
        "????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check31(table, 1, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 1, 1));

    CHECK_EQUAL(true, target.Check31(table, 6, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 6, 1));

    CHECK_EQUAL(true, target.Check31(table, 10, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 10, 2));

    CHECK_EQUAL(true, target.Check31(table, 13, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 13, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????",
        "?#C??$#??$$??C$?",
        "?$$??$C??C#??#$?",
        "????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check31(table, 2, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 1));

    CHECK_EQUAL(true, target.Check31(table, 6, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 6, 2));

    CHECK_EQUAL(true, target.Check31(table, 9, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 9, 2));

    CHECK_EQUAL(true, target.Check31(table, 13, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 13, 1));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check32) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????",
        "?C$??$C??#$??$#?",
        "?$#??#$??$C??C$?",
        "????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check32(table, 1, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 1, 1));

    CHECK_EQUAL(true, target.Check32(table, 6, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 6, 1));

    CHECK_EQUAL(true, target.Check32(table, 10, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 10, 2));

    CHECK_EQUAL(true, target.Check32(table, 13, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 13, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check33) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?#$???#C#???$#???#??",
        "?C #??$ $??# C??$ $?",
        "?#$????#????$#??#C#?",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check33(table, goals, 1, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 1, 2));

    CHECK_EQUAL(true, target.Check33(table, goals, 7, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 7, 1));

    CHECK_EQUAL(true, target.Check33(table, goals, 13, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 13, 2));

    CHECK_EQUAL(true, target.Check33(table, goals, 17, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 17, 3));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check34) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?#C???#$#???$#???#??",
        "?$ #??$ C??# $??C $?",
        "?#$????#????C#??#$#?",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check34(table, goals, 2, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 1));

    CHECK_EQUAL(true, target.Check34(table, goals, 8, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 2));

    CHECK_EQUAL(true, target.Check34(table, goals, 12, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 3));

    CHECK_EQUAL(true, target.Check34(table, goals, 16, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 16, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?#$???#$#???C#???#??",
        "?$ #??C $??# $??$ C?",
        "?#C????#????$#??#$#?",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check34(table, goals, 2, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 3));

    CHECK_EQUAL(true, target.Check34(table, goals, 6, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 6, 2));

    CHECK_EQUAL(true, target.Check34(table, goals, 12, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 1));

    CHECK_EQUAL(true, target.Check34(table, goals, 18, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 18, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check35) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?#C????##??#$????$#?",
        "?# $??$ C??$ #??C $?",
        "??$#??#$????C#??##??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check35(table, goals, 2, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 1));

    CHECK_EQUAL(true, target.Check35(table, goals, 8, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 2));

    CHECK_EQUAL(true, target.Check35(table, goals, 12, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 3));

    CHECK_EQUAL(true, target.Check35(table, goals, 16, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 16, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "??C#??#$????$#??##??",
        "?$ #??$ C??# $??C $?",
        "?#$????##??#C????$#?",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check35(table, goals, 2, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 1));

    CHECK_EQUAL(true, target.Check35(table, goals, 8, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 2));

    CHECK_EQUAL(true, target.Check35(table, goals, 12, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 3));

    CHECK_EQUAL(true, target.Check35(table, goals, 16, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 16, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check36) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?#$????##??#$????C#?",
        "?# C??$ $??C #??$ $?",
        "??$#??#C????$#??##??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check36(table, goals, 3, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 3, 2));

    CHECK_EQUAL(true, target.Check36(table, goals, 7, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 7, 3));

    CHECK_EQUAL(true, target.Check36(table, goals, 11, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 11, 2));

    CHECK_EQUAL(true, target.Check36(table, goals, 17, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 17, 1));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "??$#??#C????$#??##??",
        "?C #??$ $??# C??$ $?",
        "?#$????##??#$????C#?",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check36(table, goals, 1, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 1, 2));

    CHECK_EQUAL(true, target.Check36(table, goals, 7, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 7, 1));

    CHECK_EQUAL(true, target.Check36(table, goals, 13, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 13, 2));

    CHECK_EQUAL(true, target.Check36(table, goals, 17, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 17, 3));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check37) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "??#????#???$$????C$?",
        "?# C??$ #??C #??# $?",
        "??$$??$C????#????#??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check37(table, goals, 3, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 3, 2));

    CHECK_EQUAL(true, target.Check37(table, goals, 7, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 7, 3));

    CHECK_EQUAL(true, target.Check37(table, goals, 11, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 11, 2));

    CHECK_EQUAL(true, target.Check37(table, goals, 17, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 17, 1));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "??#????#???$C????$$?",
        "?# $??C #??$ #??# C?",
        "??C$??$$????#????#??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check37(table, goals, 2, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 3));

    CHECK_EQUAL(true, target.Check37(table, goals, 6, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 6, 2));

    CHECK_EQUAL(true, target.Check37(table, goals, 12, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 1));

    CHECK_EQUAL(true, target.Check37(table, goals, 18, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 18, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check38) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "??#????#???C$????$C?",
        "?# $??$ #??$ #??# $?",
        "??$C??C$????#????#??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check38(table, goals, 3, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 3, 3));

    CHECK_EQUAL(true, target.Check38(table, goals, 6, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 6, 3));

    CHECK_EQUAL(true, target.Check38(table, goals, 11, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 11, 1));

    CHECK_EQUAL(true, target.Check38(table, goals, 18, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 18, 1));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check41) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????",
        "?C$??$C??$$??$$?",
        "?$$??$$??$C??C$?",
        "????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check41(table, 1, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 1, 1));

    CHECK_EQUAL(true, target.Check41(table, 6, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 6, 1));

    CHECK_EQUAL(true, target.Check41(table, 10, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 10, 2));

    CHECK_EQUAL(true, target.Check41(table, 13, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 13, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check42) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "??C#??#$????$#??#$??",
        "?$ $??$ C??$ $??C $?",
        "?#$????$#??#C????$#?",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check42(table, goals, 2, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 1));

    CHECK_EQUAL(true, target.Check42(table, goals, 8, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 2));

    CHECK_EQUAL(true, target.Check42(table, goals, 12, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 3));

    CHECK_EQUAL(true, target.Check42(table, goals, 16, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 16, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "??$#??#C????$#??#$??",
        "?C $??$ $??$ C??$ $?",
        "?#$????$#??#$????C#?",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check42(table, goals, 1, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 1, 2));

    CHECK_EQUAL(true, target.Check42(table, goals, 7, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 7, 1));

    CHECK_EQUAL(true, target.Check42(table, goals, 13, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 13, 2));

    CHECK_EQUAL(true, target.Check42(table, goals, 17, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 17, 3));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check43) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?#C????##??$$????$$?",
        "?# $??$ C??$ #??C $?",
        "??$$??$$????C#??##??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check43(table, goals, 2, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 1));

    CHECK_EQUAL(true, target.Check43(table, goals, 8, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 2));

    CHECK_EQUAL(true, target.Check43(table, goals, 12, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 3));

    CHECK_EQUAL(true, target.Check43(table, goals, 16, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 16, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "??C#??$$????$$??##??",
        "?$ #??$ C??# $??C $?",
        "?$$????##??#C????$$?",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check43(table, goals, 2, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 1));

    CHECK_EQUAL(true, target.Check43(table, goals, 8, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 2));

    CHECK_EQUAL(true, target.Check43(table, goals, 12, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 3));

    CHECK_EQUAL(true, target.Check43(table, goals, 16, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 16, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check44) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?#$????##??$$????C$?",
        "?# C??$ $??C #??$ $?",
        "??$$??$C????$#??##??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check44(table, goals, 3, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 3, 2));

    CHECK_EQUAL(true, target.Check44(table, goals, 7, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 7, 3));

    CHECK_EQUAL(true, target.Check44(table, goals, 11, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 11, 2));

    CHECK_EQUAL(true, target.Check44(table, goals, 17, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 17, 1));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "??$#??$C????$$??##??",
        "?C #??$ $??# C??$ $?",
        "?$$????##??#$????C$?",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check44(table, goals, 1, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 1, 2));

    CHECK_EQUAL(true, target.Check44(table, goals, 7, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 7, 1));

    CHECK_EQUAL(true, target.Check44(table, goals, 13, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 13, 2));

    CHECK_EQUAL(true, target.Check44(table, goals, 17, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 17, 3));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check45) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?#$????##??C$????$C?",
        "?# $??$ $??$ #??$ $?",
        "??$C??C$????$#??##??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check45(table, goals, 3, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 3, 3));

    CHECK_EQUAL(true, target.Check45(table, goals, 6, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 6, 3));

    CHECK_EQUAL(true, target.Check45(table, goals, 11, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 11, 1));

    CHECK_EQUAL(true, target.Check45(table, goals, 18, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 18, 1));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "??$#??C$????$C??##??",
        "?$ #??$ $??# $??$ $?",
        "?C$????##??#$????$C?",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check45(table, goals, 1, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 1, 3));

    CHECK_EQUAL(true, target.Check45(table, goals, 6, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 6, 1));

    CHECK_EQUAL(true, target.Check45(table, goals, 13, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 13, 1));

    CHECK_EQUAL(true, target.Check45(table, goals, 18, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 18, 3));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check46) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?#$????##??$C????$$?",
        "?# $??C $??$ #??$ C?",
        "??C$??$$????$#??##??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check46(table, goals, 2, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 3));

    CHECK_EQUAL(true, target.Check46(table, goals, 6, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 6, 2));

    CHECK_EQUAL(true, target.Check46(table, goals, 12, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 1));

    CHECK_EQUAL(true, target.Check46(table, goals, 18, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 18, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "??$#??$$????C$??##??",
        "?$ #??C $??# $??$ C?",
        "?$C????##??#$????$$?",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check46(table, goals, 2, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 3));

    CHECK_EQUAL(true, target.Check46(table, goals, 6, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 6, 2));

    CHECK_EQUAL(true, target.Check46(table, goals, 12, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 12, 1));

    CHECK_EQUAL(true, target.Check46(table, goals, 18, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 18, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check61) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?$$????$$??$$????C$?",
        "?$ C??$ $??C $??$ $?",
        "??$$??$C????$$??$$??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check61(table, goals, 3, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 3, 2));

    CHECK_EQUAL(true, target.Check61(table, goals, 7, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 7, 3));

    CHECK_EQUAL(true, target.Check61(table, goals, 11, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 11, 2));

    CHECK_EQUAL(true, target.Check61(table, goals, 17, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 17, 1));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check62) {
  try {
    std::vector<std::string> board = {
      // 01234567890123456789
        "????????????????????",
        "?C$????$C??$$????$$?",
        "?$ $??$ $??$ $??$ $?",
        "??$$??$$????$C??C$??",
        "????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check62(table, goals, 1, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 1, 1));

    CHECK_EQUAL(true, target.Check62(table, goals, 8, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 1));

    CHECK_EQUAL(true, target.Check62(table, goals, 13, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 13, 3));

    CHECK_EQUAL(true, target.Check62(table, goals, 16, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 16, 3));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check4001) {
  try {
    std::vector<std::string> board = {
      // 012345678901234567890123
        "????????????????????????",
        "??###??###?????$#??#C???",
        "?#.$C??$$.#????$#??#$???",
        "?#$??????$#??C$.#??#.$$?",
        "?#$??????C#??###????###?",
        "????????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check4001(table, goals, 4, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 4, 2));

    CHECK_EQUAL(true, target.Check4001(table, goals, 9, 4));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 9, 4));

    CHECK_EQUAL(true, target.Check4001(table, goals, 13, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 13, 3));

    CHECK_EQUAL(true, target.Check4001(table, goals, 20, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 20, 1));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
      // 012345678901234567890123
        "????????????????????????",
        "??###??###?????C#??#$???",
        "?#.$$??C$.#????$#??#$???",
        "?#$??????$#??$$.#??#.$C?",
        "?#C??????$#??###????###?",
        "????????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check4001(table, goals, 2, 4));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 4));

    CHECK_EQUAL(true, target.Check4001(table, goals, 7, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 7, 2));

    CHECK_EQUAL(true, target.Check4001(table, goals, 15, 1));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 15, 1));

    CHECK_EQUAL(true, target.Check4001(table, goals, 22, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 22, 3));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
TEST(UnmovableFinder2, Check4002) {
  try {
    std::vector<std::string> board = {
      // 012345678901234567890123
        "????????????????????????",
        "??###??###?????$#??#$???",
        "?#.C$??$$.#????$#??#C???",
        "?#$??????C#??$C.#??#.$$?",
        "?#$??????$#??###????###?",
        "????????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check4002(table, goals, 3, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 3, 2));

    CHECK_EQUAL(true, target.Check4002(table, goals, 9, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 9, 3));

    CHECK_EQUAL(true, target.Check4002(table, goals, 14, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 14, 3));

    CHECK_EQUAL(true, target.Check4002(table, goals, 20, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 20, 2));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }

  try {
    std::vector<std::string> board = {
      // 012345678901234567890123
        "????????????????????????",
        "??###??###?????$#??#$???",
        "?#.$$??$C.#????C#??#$???",
        "?#C??????$#??$$.#??#.C$?",
        "?#$??????$#??###????###?",
        "????????????????????????"
    };
    Table table;
    GoalsHolder goals;
    BoardCreator::Create(board, table, goals);
    UnmovableFinder target;

    CHECK_EQUAL(true, target.Check4002(table, goals, 2, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 2, 3));

    CHECK_EQUAL(true, target.Check4002(table, goals, 8, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 8, 2));

    CHECK_EQUAL(true, target.Check4002(table, goals, 15, 2));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 15, 2));

    CHECK_EQUAL(true, target.Check4002(table, goals, 21, 3));
    CHECK_EQUAL(true, target.Unmovable(table, goals, 21, 3));
  } catch (std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}
