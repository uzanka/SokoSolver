#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED

#define TABLE_2
//#define TABLE_8
//#define TABLE_S

#if defined(TABLE_2)
#include "Table2.h"
typedef Table2 Table;
const static int kSpace        = 0;
const static int kBox          = 1;
const static int kPlayer       = 2;
const static int kWall         = 3;

#elif defined(TABLE_8)
#include "Table8.h"
typedef Table8 Table;
const static int kSpace        = 0;
const static int kBox          = 1;
const static int kPlayer       = 2;
const static int kWall         = 3;
const static int kGoal         = 4;
const static int kBoxOnGoal    = 5;
const static int kPlayerOnGoal = 6;

#elif defined(TABLE_S)
#include "TableS.h"
typedef TableS Table;
const static int kSpace        = ' ';
const static int kBox          = '$';
const static int kPlayer       = '@';
const static int kWall         = '#';
const static int kGoal         = '.';
const static int kBoxOnGoal    = '*';
const static int kPlayerOnGoal = '+';

#endif

#endif  // TABLE_INCLUDED
