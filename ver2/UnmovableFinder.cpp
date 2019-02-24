#include "UnmovableFinder.h"

#define ISWAL(x, y) (T.Get(x, y) == kWall)
#define ISBOX(x, y) (T.Get(x, y) == kBox)
//#define ISGOA(x, y) (G.Goal(x, y) == true)
//#define ISSPC(x, y) (T.Get(x, y) == kSpace)
#define ISN_S(x, y) ((G.Goal(x, y) == false) && (T.Get(x, y) == kSpace))
#define ISG_S(x, y) ((G.Goal(x, y) == true) && (T.Get(x, y) == kSpace))

///////////////////////////////////////////////////////////////////////////////
UnmovableFinder::UnmovableFinder() {
}

///////////////////////////////////////////////////////////////////////////////
UnmovableFinder::~UnmovableFinder() {
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Unmovable(const Table& table, const GoalsHolder& goals, const int x, const int y) {
  if (table.Get(x, y) != kBox) return false;
  if (!goals.Goal(x, y)) {
    if (Check11(table, x, y)) return true;
    if (Check21(table, x, y)) return true;
    if (Check22(table, x, y)) return true;
    if (Check23(table, goals, x, y)) return true;
    if (Check24(table, goals, x, y)) return true;
    if (Check25(table, goals, x, y)) return true;
    if (Check26(table, goals, x, y)) return true;
    if (Check27(table, goals, x, y)) return true;
    if (Check28(table, goals, x, y)) return true;
    if (Check31(table, x, y)) return true;
    if (Check32(table, x, y)) return true;
    if (Check33(table, goals, x, y)) return true;
    if (Check34(table, goals, x, y)) return true;
    if (Check35(table, goals, x, y)) return true;
    if (Check36(table, goals, x, y)) return true;
    if (Check37(table, goals, x, y)) return true;
    if (Check38(table, goals, x, y)) return true;
    if (Check41(table, x, y)) return true;
    if (Check42(table, goals, x, y)) return true;
    if (Check43(table, goals, x, y)) return true;
    if (Check44(table, goals, x, y)) return true;
    if (Check45(table, goals, x, y)) return true;
    if (Check46(table, goals, x, y)) return true;
    if (Check61(table, goals, x, y)) return true;
    if (Check62(table, goals, x, y)) return true;
  } else {
  }

  if (Check4001(table, goals, x, y)) return true;
  if (Check4002(table, goals, x, y)) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check11(const Table& T, const int x, const int y) {
  // #?  C#  ?#  #C
  // C#  #?  #C  ?#

  if (ISWAL(x+1, y) && ISWAL(x, y-1)) return true;
  if (ISWAL(x+1, y) && ISWAL(x, y+1)) return true;
  if (ISWAL(x-1, y) && ISWAL(x, y-1)) return true;
  if (ISWAL(x-1, y) && ISWAL(x, y+1)) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check21(const Table& T, const int x, const int y) {
  // C#  $C  #$  ##
  // $#  ##  #C  C$

  if (/*Current*/        ISWAL(x+1, y  )
   && ISBOX(x  , y+1) && ISWAL(x+1, y+1)
  ) return true;

  if (ISBOX(x-1, y  )    /*Current*/
   && ISWAL(x-1, y+1) && ISWAL(x  , y+1)
  ) return true;

  if (ISWAL(x-1, y-1) && ISBOX(x  , y-1)
   && ISWAL(x-1, y  )    /*Current*/
  ) return true;

  if (ISWAL(x  , y-1) && ISWAL(x+1, y-1)
      /*Current*/     && ISBOX(x+1, y  )
  ) return true;

  // $#  C$  #C  ##
  // C#  ##  #$  $C

  if (ISBOX(x  , y-1) && ISWAL(x+1, y-1)
      /*Current*/     && ISWAL(x+1, y  )
  ) return true;

  if (/*Current*/        ISBOX(x+1, y  )
   && ISWAL(x  , y+1) && ISWAL(x+1, y+1)
  ) return true;

  if (ISWAL(x-1, y  )    /*Current*/
   && ISWAL(x-1, y+1) && ISBOX(x  , y+1)
  ) return true;

  if (ISWAL(x-1, y-1) && ISWAL(x  , y-1)
   && ISBOX(x-1, y  )    /*Current*/
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check22(const Table& T, const int x, const int y) {
  // ?C#  #?  ?$#  #?
  // #$?  $C  #C?  C$
  //      ?#       ?#

  if (                   /*Current*/       ISWAL(x+1, y  )
   && ISWAL(x-1, y+1) && ISBOX(x  , y+1)
  ) return true;

  if (ISWAL(x-1, y-1)
   && ISBOX(x-1, y  )    /*Current*/
                      && ISWAL(x  , y+1)
  ) return true;

  if (                   ISBOX(x  , y-1) && ISWAL(x+1, y-1)
   && ISWAL(x-1, y  )    /*Current*/
  ) return true;

  if (ISWAL(x  , y-1)
      /*Current*/     && ISBOX(x+1, y  )
                      && ISWAL(x+1, y+1)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check23(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // ?##  ##?  ?b#  #C?
  // #-C  b-#  C-#  #-b
  // #b?  ?C#  ##?  ?##

  if (                   ISWAL(x-1, y-1) && ISWAL(x  , y-1)
   && ISWAL(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
   && ISWAL(x-2, y+1) && ISBOX(x-1, y+1)
  ) return true;

  if (ISWAL(x-1, y-2) && ISWAL(x  , y-2)
   && ISBOX(x-1, y-1) && ISN_S(x  , y-1) && ISWAL(x+1, y-1)
                         /*Current*/     && ISWAL(x+1, y  )
  ) return true;

  if (                   ISBOX(x+1, y-1) && ISWAL(x+2, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISWAL(x+2, y  )
   && ISWAL(x  , y+1) && ISWAL(x+1, y+1)
  ) return true;

  if (ISWAL(x-1, y  )    /*Current*/
   && ISWAL(x-1, y+1) && ISN_S(x  , y+1) && ISBOX(x+1, y+1)
                      && ISWAL(x  , y+2) && ISWAL(x+1, y+2)
  ) return true;

  // ?##  ##?  ?C#  #b?
  // #-b  C-#  b-#  #-C
  // #C?  ?b#  ##?  ?##

  if (                   ISWAL(x  , y-2) && ISWAL(x+1, y-2)
   && ISWAL(x-1, y-1) && ISN_S(x  , y-1) && ISBOX(x+1, y-1)
   && ISWAL(x-1, y  )    /*Current*/
  ) return true;

  if (ISWAL(x  , y-1) && ISWAL(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISWAL(x+2, y  )
                      && ISBOX(x+1, y+1) && ISWAL(x+2, y+1)
  ) return true;

  if (                   /*Current*/        ISWAL(x+1, y  )
   && ISBOX(x-1, y+1) && ISN_S(x  , y+1) && ISWAL(x+1, y+1)
   && ISWAL(x-1, y+2) && ISWAL(x  , y+2)
  ) return true;

  if (ISWAL(x-2, y-1) && ISBOX(x-1, y-1)
   && ISWAL(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISWAL(x-1, y+1) && ISWAL(x  , y+1)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check24(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // #C?  ?b#  ?#?  ?#?
  // b-#  #-C  #-b  C-#
  // ?#?  ?#?  ?C#  #b?

  if (ISWAL(x-1, y  )    /*Current*/
   && ISBOX(x-1, y+1) && ISN_S(x  , y+1) && ISWAL(x+1, y+1)
                      && ISWAL(x  , y+2)
  ) return true;

  if (                   ISBOX(x-1, y-1) && ISWAL(x  , y-1)
   && ISWAL(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISWAL(x-1, y+1)
  ) return true;

  if (                   ISWAL(x  , y-2)
   && ISWAL(x-1, y-1) && ISN_S(x  , y-1) && ISBOX(x+1, y-1)
                         /*Current*/     && ISWAL(x+1, y  )
  ) return true;

  if (                   ISWAL(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISWAL(x+2, y  )
   && ISWAL(x  , y+1) && ISBOX(x+1, y+1)
  ) return true;

  // ?C#  ?#?  ?#?  #b?
  // #-b  #-C  b-#  C-#
  // ?#?  ?b#  #C?  ?#?

  if (                   /*Current*/        ISWAL(x+1, y  )
   && ISWAL(x-1, y+1) && ISN_S(x  , y+1) && ISBOX(x+1, y+1)
                      && ISWAL(x  , y+2)
  ) return true;

  if (                   ISWAL(x-1, y-1)
   && ISWAL(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISBOX(x-1, y+1) && ISWAL(x  , y+1)
  ) return true;

  if (                   ISWAL(x  , y-2)
   && ISBOX(x-1, y-1) && ISN_S(x  , y-1) && ISWAL(x+1, y-1)
   && ISWAL(x-1, y  )    /*Current*/
  ) return true;

  if (ISWAL(x  , y-1) && ISBOX(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISWAL(x+2, y  )
                      && ISWAL(x+1, y+1)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check25(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // bC?  ?#b  ?#?  ?#?
  // #-#  #-C  #-#  C-#
  // ?#?  ?#?  ?Cb  b#?

  if (ISBOX(x-1, y  )    /*Current*/
   && ISWAL(x-1, y+1) && ISN_S(x  , y+1) && ISWAL(x+1, y+1)
                      && ISWAL(x  , y+2)
  ) return true;

  if (                   ISWAL(x-1, y-1) && ISBOX(x  , y-1)
   && ISWAL(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISWAL(x-1, y+1)
  ) return true;

  if (                   ISWAL(x  , y-2)
   && ISWAL(x-1, y-1) && ISN_S(x  , y-1) && ISWAL(x+1, y-1)
                         /*Current*/     && ISBOX(x+1, y  )
  ) return true;

  if (                   ISWAL(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISWAL(x+2, y  )
   && ISBOX(x  , y+1) && ISWAL(x+1, y+1)
  ) return true;

  // ?Cb  ?#?  ?#?  b#?
  // #-#  #-C  #-#  C-#
  // ?#?  ?#b  bC?  ?#?

  if (                   /*Current*/        ISBOX(x+1, y  )
   && ISWAL(x-1, y+1) && ISN_S(x  , y+1) && ISWAL(x+1, y+1)
                      && ISWAL(x  , y+2)
  ) return true;

  if (                   ISWAL(x-1, y-1)
   && ISWAL(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISWAL(x-1, y+1) && ISBOX(x  , y+1)
  ) return true;

  if (                   ISWAL(x  , y-2)
   && ISWAL(x-1, y-1) && ISN_S(x  , y-1) && ISWAL(x+1, y-1)
   && ISBOX(x-1, y  )    /*Current*/
  ) return true;

  if (ISBOX(x  , y-1) && ISWAL(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISWAL(x+2, y  )
                      && ISWAL(x+1, y+1)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check26(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // Cb?  ?#C  ?#?  ?#?
  // #-#  #-b  #-#  b-#
  // ?#?  ?#?  ?bC  C#?

  if (/*Current*/        ISBOX(x+1, y  )
   && ISWAL(x  , y+1) && ISN_S(x+1, y+1) && ISWAL(x+2, y+1)
                      && ISWAL(x+1, y+2)
  ) return true;

  if (                   ISWAL(x-1, y  )    /*Current*/
   && ISWAL(x-2, y+1) && ISN_S(x-1, y+1) && ISBOX(x  , y+1)
                      && ISWAL(x-1, y+2)
  ) return true;

  if (                   ISWAL(x-1, y-2)
   && ISWAL(x-2, y-1) && ISN_S(x-1, y-1) && ISWAL(x  , y-1)
                      && ISBOX(x-1, y  )    /*Current*/
  ) return true;

  if (                   ISWAL(x+1, y-2)
   && ISBOX(x  , y-1) && ISN_S(x+1, y-1) && ISWAL(x+2, y-1)
   /*Current*/        && ISWAL(x+1, y  )
  ) return true;

  // ?bC  ?#?  ?#?  C#?
  // #-#  #-b  #-#  b-#
  // ?#?  ?#C  Cb?  ?#?

  if (                   ISBOX(x-1, y  )    /*Current*/
   && ISWAL(x-2, y+1) && ISN_S(x-1, y+1) && ISWAL(x  , y+1)
                      && ISWAL(x-1, y+2)
  ) return true;

  if (                   ISWAL(x-1, y-2)
   && ISWAL(x-2, y-1) && ISN_S(x-1, y-1) && ISBOX(x  , y-1)
                      && ISWAL(x-1, y  )    /*Current*/
  ) return true;

  if (                   ISWAL(x+1, y-2)
   && ISWAL(x  , y-1) && ISN_S(x+1, y-1) && ISWAL(x+2, y-1)
      /*Current*/     && ISBOX(x+1, y  )
  ) return true;

  if (/*Current*/        ISWAL(x+1, y  )
   && ISBOX(x  , y+1) && ISN_S(x+1, y+1) && ISWAL(x+2, y+1)
                      && ISWAL(x+1, y+2)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check27(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // #C?  ###  ?b#  ?#?
  // #-#  b-C  #-#  C-b
  // #b?  ?#?  ?C#  ###

  if (ISWAL(x-1, y  )    /*Current*/
   && ISWAL(x-1, y+1) && ISN_S(x  , y+1) && ISWAL(x+1, y+1)
   && ISWAL(x-1, y+2) && ISBOX(x  , y+2)
  ) return true;

  if (ISWAL(x-2, y-1) && ISWAL(x-1, y-1) && ISWAL(x  , y-1)
   && ISBOX(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISWAL(x-1, y+1)
  ) return true;

  if (                   ISBOX(x  , y-2) && ISWAL(x+1, y-2)
   && ISWAL(x-1, y-1) && ISN_S(x  , y-1) && ISWAL(x+1, y-1)
                         /*Current*/     && ISWAL(x+1, y  )
  ) return true;

  if (                   ISWAL(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISBOX(x+2, y  )
   && ISWAL(x  , y+1) && ISWAL(x+1, y+1) && ISWAL(x+2, y+1)
  ) return true;

  // #b?  ###  ?C#  ?#?
  // #-#  C-b  #-#  b-C
  // #C?  ?#?  ?b#  ###

  if (ISWAL(x-1, y-2) && ISBOX(x  , y-2)
   && ISWAL(x-1, y-1) && ISN_S(x  , y-1) && ISWAL(x+1, y-1)
   && ISWAL(x-1, y  )    /*Current*/
  ) return true;

  if (ISWAL(x  , y-1) && ISWAL(x+1, y-1) && ISWAL(x+2, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISBOX(x+2, y  )
                      && ISWAL(x+1, y+1)
  ) return true;

  if (                   /*Current*/        ISWAL(x+1, y  )
   && ISWAL(x-1, y+1) && ISN_S(x  , y+1) && ISWAL(x+1, y+1)
                      && ISBOX(x  , y+2) && ISWAL(x+1, y+2)
  ) return true;

  if (                   ISWAL(x-1, y-1)
   && ISBOX(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
   && ISWAL(x-2, y+1) && ISWAL(x-1, y+1) && ISWAL(x  , y+1)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check28(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // #C?  ?##  #b?  ?##
  // #-#  b-C  #-#  C-b
  // ?b#  ##?  ?C#  ##?

  if (ISWAL(x-1, y  )    /*Current*/
   && ISWAL(x-1, y+1) && ISN_S(x  , y+1) && ISWAL(x+1, y+1)
                      && ISBOX(x  , y+2) && ISWAL(x+1, y+2)
  ) return true;

  if (                   ISWAL(x-1, y-1) && ISWAL(x  , y-1)
   && ISBOX(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
   && ISWAL(x-2, y+1) && ISWAL(x-1, y+1)
  ) return true;

  if (ISWAL(x-1, y-2) && ISBOX(x  , y-2)
   && ISWAL(x-1, y-1) && ISN_S(x  , y-1) && ISWAL(x+1, y-1)
                         /*Current*/     && ISWAL(x+1, y  )
  ) return true;

  if (                   ISWAL(x+1, y-1) && ISWAL(x+2, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISBOX(x+2, y  )
   && ISWAL(x  , y+1) && ISWAL(x+1, y+1)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check31(const Table& T, const int x, const int y) {
  // C#  $C  $$  #$
  // $$  $#  #C  C$

  if (/*Current*/        ISWAL(x+1, y  )
   && ISBOX(x  , y+1) && ISBOX(x+1, y+1)
  ) return true;

  if (ISBOX(x-1, y  )    /*Current*/
   && ISBOX(x-1, y+1) && ISWAL(x  , y+1)
  ) return true;

  if (ISBOX(x-1, y-1) && ISBOX(x  , y-1)
   && ISWAL(x-1, y  )    /*Current*/
  ) return true;

  if (ISWAL(x  , y-1) && ISBOX(x+1, y-1)
      /*Current*/     && ISBOX(x+1, y  )
  ) return true;

  // #C  $#  $$  C$
  // $$  $C  C#  #$

  if (ISWAL(x-1, y  )    /*Current*/
   && ISBOX(x-1, y+1) && ISBOX(x  , y+1)
  ) return true;

  if (ISBOX(x-1, y-1) && ISWAL(x  , y-1)
   && ISBOX(x-1, y  )    /*Current*/
  ) return true;

  if (ISBOX(x  , y-1) && ISBOX(x+1, y-1)
      /*Current*/     && ISWAL(x+1, y  )
  ) return true;

  if (/*Current*/        ISBOX(x+1, y  )
   && ISWAL(x  , y+1) && ISBOX(x+1, y+1)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check32(const Table& T, const int x, const int y) {
  // C$  $C  #$  $#
  // $#  #$  $C  C$

  if (/*Current*/        ISBOX(x+1, y  )
   && ISBOX(x  , y+1) && ISWAL(x+1, y+1)
  ) return true;

  if (ISBOX(x-1, y  )    /*Current*/
   && ISWAL(x-1, y+1) && ISBOX(x  , y+1)
  ) return true;

  if (ISWAL(x-1, y-1) && ISBOX(x-1, y  )
   && ISBOX(x  , y-1)    /*Current*/
  ) return true;

  if (ISBOX(x  , y-1) && ISWAL(x+1, y-1)
      /*Current*/     && ISBOX(x+1, y  )
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check33(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // #b?  #C#  ?b#  ?#?
  // C-#  b-b  #-C  b-b
  // #b?  ?#?  ?b#  #C#

  if (ISWAL(x  , y-1) && ISBOX(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISWAL(x+2, y  )
   && ISWAL(x  , y+1) && ISBOX(x+1, y+1)
  ) return true;

  if (ISWAL(x-1, y  )    /*Current*/     && ISWAL(x+1, y  )
   && ISBOX(x-1, y+1) && ISN_S(x  , y+1) && ISBOX(x+1, y+1)
                      && ISWAL(x  , y+2)
  ) return true;

  if (                   ISBOX(x-1, y-1) && ISWAL(x  , y-1)
   && ISWAL(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISBOX(x-1, y+1) && ISWAL(x  , y+1)
  ) return true;

  if (                   ISWAL(x  , y-2)
   && ISBOX(x-1, y-1) && ISN_S(x  , y-1) && ISBOX(x+1, y-1)
   && ISWAL(x-1, y  )    /*Current*/     && ISWAL(x+1, y  )
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check34(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // #C?  #b#  ?b#  ?#?
  // b-#  b-C  #-b  C-b
  // #b?  ?#?  ?C#  #b#

  if (ISWAL(x-1, y  )    /*Current*/
   && ISBOX(x-1, y+1) && ISN_S(x  , y+1) && ISWAL(x+1, y+1)
   && ISWAL(x-1, y+2) && ISBOX(x  , y+2)
  ) return true;

  if (ISWAL(x-2, y-1) && ISBOX(x-1, y-1) && ISWAL(x  , y-1)
   && ISBOX(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISWAL(x-1, y+1)
  ) return true;

  if (                   ISBOX(x  , y-2) && ISWAL(x+1, y-2)
   && ISWAL(x-1, y-1) && ISN_S(x  , y-1) && ISBOX(x+1, y-1)
                         /*Current*/     && ISWAL(x+1, y  )
  ) return true;

  if (                   ISWAL(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISBOX(x+2, y  )
   && ISWAL(x  , y+1) && ISBOX(x+1, y+1) && ISWAL(x+2, y+1)
  ) return true;

  // #b?  #b#  ?C#  ?#?
  // b-#  C-b  #-b  b-C
  // #C?  ?#?  ?b#  #b#

  if (ISWAL(x-1, y-2) && ISBOX(x  , y-2)
   && ISBOX(x-1, y-1) && ISN_S(x  , y-1) && ISWAL(x+1, y-1)
   && ISWAL(x-1, y  )    /*Current*/
  ) return true;

  if (ISWAL(x  , y-1) && ISBOX(x+1, y-1) && ISWAL(x+2, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISBOX(x+2, y  )
                      && ISWAL(x+1, y+1)
  ) return true;

  if (                   /*Current*/        ISWAL(x+1, y  )
   && ISWAL(x-1, y+1) && ISN_S(x  , y+1) && ISBOX(x+1, y+1)
                      && ISBOX(x  , y+2) && ISWAL(x+1, y+2)
  ) return true;

  if (                   ISWAL(x-1, y-1)
   && ISBOX(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
   && ISWAL(x-2, y+1) && ISBOX(x-1, y+1) && ISWAL(x  , y+1)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check35(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // #C?  ?##  #b?  ?b#
  // #-b  b-C  b-#  C-b
  // ?b#  #b?  ?C#  ##?

  if (ISWAL(x-1, y  )    /*Current*/
   && ISWAL(x-1, y+1) && ISN_S(x  , y+1) && ISBOX(x+1, y+1)
                      && ISBOX(x  , y+2) && ISWAL(x+1, y+2)
  ) return true;

  if (                   ISWAL(x-1, y-1) && ISWAL(x  , y-1)
   && ISBOX(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
   && ISWAL(x-2, y+1) && ISBOX(x-1, y+1)
  ) return true;

  if (ISWAL(x-1, y-2) && ISBOX(x  , y-2)
   && ISBOX(x-1, y-1) && ISN_S(x  , y-1) && ISWAL(x+1, y-1)
                         /*Current*/     && ISWAL(x+1, y  )
  ) return true;

  if (                   ISBOX(x+1, y-1) && ISWAL(x+2, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISBOX(x+2, y  )
   && ISWAL(x  , y+1) && ISWAL(x+1, y+1)
  ) return true;

  // ?C#  #b?  ?b#  ##?
  // b-#  b-C  #-b  C-b
  // #b?  ?##  #C?  ?b#

  if (                   /*Current*/        ISWAL(x+1, y  ) 
   && ISBOX(x-1, y+1) && ISN_S(x  , y+1) && ISWAL(x+1, y+1)
   && ISWAL(x-1, y+2) && ISBOX(x  , y+2)
  ) return true;

  if (ISWAL(x-2, y-1) && ISBOX(x-1, y-1)
   && ISBOX(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISWAL(x-1, y+1) && ISWAL(x  , y+1)
  ) return true;

  if (                   ISBOX(x  , y-2) && ISWAL(x+1, y-2)
   && ISWAL(x-1, y-1) && ISN_S(x  , y-1) && ISBOX(x+1, y-1)
   && ISWAL(x-1, y  )    /*Current*/
  ) return true;

  if (ISWAL(x  , y-1) && ISWAL(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISBOX(x+2, y  )
                      && ISBOX(x+1, y+1) && ISWAL(x+2, y+1)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check36(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // #b?  ?##  #b?  ?C#
  // #-C  b-b  C-#  b-b
  // ?b#  #C?  ?b#  ##?

  if (ISWAL(x-2, y-1) && ISBOX(x-1, y-1)
   && ISWAL(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISBOX(x-1, y+1) && ISWAL(x  , y+1)
  ) return true;

  if (                   ISWAL(x  , y-2) && ISWAL(x+1, y-2)
   && ISBOX(x-1, y-1) && ISN_S(x  , y-1) && ISBOX(x+1, y-1)
   && ISWAL(x-1, y  )    /*Current*/
  ) return true;

  if (ISWAL(x  , y-1) && ISBOX(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISWAL(x+2, y  )
                      && ISBOX(x+1, y+1) && ISWAL(x+2, y+1)
  ) return true;

  if (                   /*Current*/        ISWAL(x+1, y  )
   && ISBOX(x-1, y+1) && ISN_S(x  , y+1) && ISBOX(x+1, y+1)
   && ISWAL(x-1, y+2) && ISWAL(x  , y+2)
  ) return true;

  // ?b#  #C?  ?b#  ##?
  // C-#  b-b  #-C  b-b
  // #b?  ?##  #b?  ?C#

  if (                   ISBOX(x+1, y-1) && ISWAL(x+2, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISWAL(x+2, y  )
   && ISWAL(x  , y+1) && ISBOX(x+1, y+1)
  ) return true;

  if (ISWAL(x-1, y  )    /*Current*/
   && ISBOX(x-1, y+1) && ISN_S(x  , y+1) && ISBOX(x+1, y+1)
                      && ISWAL(x  , y+2) && ISWAL(x+1, y+2)
  ) return true;

  if (                   ISBOX(x-1, y-1) && ISWAL(x  , y-1)
   && ISWAL(x-2, y  ) && ISN_S(x-1, y  ) /*Current*/
   && ISWAL(x-2, y+1) && ISBOX(x-1, y+1)
  ) return true;

  if (ISWAL(x-1, y-2) && ISWAL(x  , y-2)
   && ISBOX(x-1, y-1) && ISN_S(x  , y-1) && ISBOX(x+1, y-1)
      /*Current*/     && ISWAL(x+1, y  )
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check37(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // ?#?  ?#?  bb?  ?Cb
  // #-C  b-#  C-#  #-b
  // ?bb  bC?  ?#?  ?#?

  if (                   ISWAL(x-1, y-1)
   && ISWAL(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISBOX(x-1, y+1) && ISBOX(x  , y+1)
  ) return true;

  if (                   ISWAL(x  , y-2)
   && ISBOX(x-1, y-1) && ISN_S(x  , y-1) && ISWAL(x+1, y-1)
   && ISBOX(x-1, y  )    /*Current*/
  ) return true;

  if (ISBOX(x  , y-1) && ISBOX(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISWAL(x+2, y  )
                      && ISWAL(x+1, y+1)
  ) return true;

  if (                   /*Current*/        ISBOX(x+1, y  )
   && ISWAL(x-1, y+1) && ISN_S(x  , y+1) && ISBOX(x+1, y+1)
                      && ISWAL(x  , y+2)
  ) return true;

  // ?#?  ?#?  bC?  ?bb
  // #-b  C-#  b-#  #-C
  // ?Cb  bb?  ?#?  ?#?

  if (                   ISWAL(x  , y-2)
   && ISWAL(x-1, y-1) && ISN_S(x  , y-1) && ISBOX(x+1, y-1)
                         /*Current*/     && ISBOX(x+1, y  )
  ) return true;

  if (                   ISWAL(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISWAL(x+2, y  )
   && ISBOX(x  , y+1) && ISBOX(x+1, y+1)
  ) return true;

  if (ISBOX(x-1, y  )    /*Current*/  
   && ISBOX(x-1, y+1) && ISN_S(x  , y+1) && ISWAL(x+1, y+1)
                      && ISWAL(x  , y+2)
  ) return true;

  if (                   ISBOX(x-1, y-1) && ISBOX(x  , y-1)
   && ISWAL(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISWAL(x-1, y+1)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check38(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // ?#?  ?#?  Cb?  ?bC
  // #-b  b-#  b-#  #-b
  // ?bC  Cb?  ?#?  ?#?

  if (                   ISWAL(x-1, y-2)
   && ISWAL(x-2, y-1) && ISN_S(x-1, y-1) && ISBOX(x  , y-1)
                      && ISBOX(x-1, y  )    /*Current*/
  ) return true;

  if (                   ISWAL(x+1, y-2)
   && ISBOX(x  , y-1) && ISN_S(x+1, y-1) && ISWAL(x+2, y-1)
      /*Current*/     && ISBOX(x+1, y  )
  ) return true;

  if (/*Current*/        ISBOX(x+1, y  )
   && ISBOX(x  , y+1) && ISN_S(x+1, y+1) && ISWAL(x+2, y+1)
                      && ISWAL(x+1, y+2)
  ) return true;

  if (                   ISBOX(x-1, y  )    /*Current*/
   && ISWAL(x-2, y+1) && ISN_S(x-1, y+1) && ISBOX(x  , y+1)
                      && ISWAL(x-1, y+2)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check41(const Table& T, const int x, const int y) {
  // C$  $C  $$  $$
  // $$  $$  $C  C$

  if (/*Current*/        ISBOX(x+1, y  )
   && ISBOX(x  , y+1) && ISBOX(x+1, y+1)
  ) return true;

  if (ISBOX(x  , y+1)    /*Current*/
   && ISBOX(x-1, y  ) && ISBOX(x-1, y+1)
  ) return true;

  if (ISBOX(x-1, y-1) && ISBOX(x, y-1)
   && ISBOX(x-1, y  )    /*Current*/
  ) return true;

  if (ISBOX(x  , y-1) && ISBOX(x+1, y-1)
   /*Current*/        && ISBOX(x+1, y  )
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check42(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // ?C#  #b?  ?b#  #b?
  // b-b  b-C  b-b  C-b
  // #b?  ?b#  #C?  ?b#

  if (                   /*Current*/        ISWAL(x+1, y  )
   && ISBOX(x-1, y+1) && ISN_S(x  , y+1) && ISBOX(x+1, y+1)
   && ISWAL(x-1, y+2) && ISBOX(x  , y+2)
  ) return true;

  if (ISWAL(x-2, y-1) && ISBOX(x-1, y-1)
   && ISBOX(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISBOX(x-1, y+1) && ISWAL(x  , y+1)
  ) return true;

  if (                   ISBOX(x  , y-2) && ISWAL(x+1, y-2)
   && ISBOX(x-1, y-1) && ISN_S(x  , y-1) && ISBOX(x+1, y-1)
   && ISWAL(x-1, y  )    /*Current*/
  ) return true;

  if (ISWAL(x  , y-1) && ISBOX(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISBOX(x+2, y  )
                      && ISBOX(x+1, y+1) && ISWAL(x+2, y+1)
  ) return true;

  // ?b#  #C?  ?b#  #b?
  // C-b  b-b  b-C  b-b
  // #b?  ?b#  #b?  ?C#

  if (                   ISBOX(x+1, y-1) && ISWAL(x+2, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISBOX(x+2, y  )
   && ISWAL(x  , y+1) && ISBOX(x+1, y+1)
  ) return true;

  if (ISWAL(x-1, y  )  /*Current*/
   && ISBOX(x-1, y+1) && ISN_S(x  , y+1) && ISBOX(x+1, y+1)
                      && ISBOX(x  , y+2) && ISWAL(x+1, y+2)
  ) return true;

  if (                   ISBOX(x-1, y-1) && ISWAL(x  , y-1)
   && ISBOX(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
   && ISWAL(x-2, y+1) && ISBOX(x-1, y+1)
  ) return true;

  if (ISWAL(x-1, y-2) && ISBOX(x  , y-2)
   && ISBOX(x-1, y-1) && ISN_S(x  , y-1) && ISBOX(x+1, y-1)
                         /*Current*/     && ISWAL(x+1, y  )
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check43(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // #C?  ?##  bb?  ?bb
  // #-b  b-C  b-#  C-b
  // ?bb  bb?  ?C#  ##?

  if (ISWAL(x-1, y  )    /*Current*/
   && ISWAL(x-1, y+1) && ISN_S(x  , y+1) && ISBOX(x+1, y+1)
                      && ISBOX(x  , y+2) && ISBOX(x+1, y+2)
  ) return true;

  if (                   ISWAL(x-1, y-1) && ISWAL(x  , y-1)
   && ISBOX(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
   && ISBOX(x-2, y+1) && ISBOX(x-1, y+1)
  ) return true;

  if (ISBOX(x-1, y-2) && ISBOX(x  , y-2)
   && ISBOX(x-1, y-1) && ISN_S(x  , y-1) && ISWAL(x+1, y-1)
                         /*Current*/     && ISWAL(x+1, y  )
  ) return true;

  if (                   ISBOX(x+1, y-1) && ISBOX(x+2, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISBOX(x+2, y  )
   && ISWAL(x  , y+1) && ISWAL(x+1, y+1)
  ) return true;

  // ?C#  bb?  ?bb  ##?
  // b-#  b-C  #-b  C-b
  // bb?  ?##  #C?  ?bb

  if (                   /*Current*/        ISWAL(x+1, y  )
   && ISBOX(x-1, y+1) && ISN_S(x  , y+1) && ISWAL(x+1, y+1)
   && ISBOX(x-1, y+2) && ISBOX(x  , y+2)
  ) return true;

  if (ISBOX(x-2, y-1) && ISBOX(x-1, y-1)
   && ISBOX(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISWAL(x-1, y+1) && ISWAL(x  , y+1)
  ) return true;

  if (                   ISBOX(x  , y-2) && ISBOX(x+1, y-2)
   && ISWAL(x-1, y-1) && ISN_S(x  , y-1) && ISBOX(x+1, y-1)
   && ISWAL(x-1, y  )    /*Current*/
  ) return true;

  if (ISWAL(x  , y-1) && ISWAL(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISBOX(x+2, y  )
                      && ISBOX(x+1, y+1) && ISBOX(x+2, y+1)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check44(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // #b?  ?##  bb?  ?Cb
  // #-C  b-b  C-#  b-b
  // ?bb  bC?  ?b#  ##?

  if (ISWAL(x-2, y-1) && ISBOX(x-1, y-1)
   && ISWAL(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISBOX(x-1, y+1) && ISBOX(x  , y+1)
  ) return true;

  if (                   ISWAL(x  , y-2) && ISWAL(x+1, y-2)
   && ISBOX(x-1, y-1) && ISN_S(x  , y-1) && ISBOX(x+1, y-1)
   && ISBOX(x-1, y  )    /*Current*/
  ) return true;

  if (ISBOX(x  , y-1) && ISBOX(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISWAL(x+2, y  )
                      && ISBOX(x+1, y+1) && ISWAL(x+2, y+1)
  ) return true;

  if (                   /*Current*/        ISBOX(x+1, y  )
   && ISBOX(x-1, y+1) && ISN_S(x  , y+1) && ISBOX(x+1, y+1)
   && ISWAL(x-1, y+2) && ISWAL(x  , y+2)
  ) return true;

  // ?b#  bC?  ?bb  ##?
  // C-#  b-b  #-C  b-b
  // bb?  ?##  #b?  ?Cb

  if (                   ISBOX(x+1, y-1) && ISWAL(x+2, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISWAL(x+2, y  )
   && ISBOX(x  , y+1) && ISBOX(x+1, y+1)
  ) return true;

  if (ISBOX(x-1, y  )    /*Current*/
   && ISBOX(x-1, y+1) && ISN_S(x  , y+1) && ISBOX(x+1, y+1)
                      && ISWAL(x  , y+2) && ISWAL(x+1, y+2)
  ) return true;

  if (                   ISBOX(x-1, y-1) && ISBOX(x  , y-1)
   && ISWAL(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
   && ISWAL(x-2, y+1) && ISBOX(x-1, y+1)
  ) return true;

  if (ISWAL(x-1, y-2) && ISWAL(x  , y-2)
   && ISBOX(x-1, y-1) && ISN_S(x  , y-1) && ISBOX(x+1, y-1)
                         /*Current*/     && ISBOX(x+1, y  )
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check45(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // #b?  ?##  Cb?  ?bC
  // #-b  b-b  b-#  b-b
  // ?bC  Cb?  ?b#  ##?

  if (ISWAL(x-2, y-2) && ISBOX(x-1, y-2)
   && ISWAL(x-2, y-1) && ISN_S(x-1, y-1) && ISBOX(x  , y-1)
                      && ISBOX(x-1, y  )    /*Current*/
  ) return true;

  if (                   ISWAL(x+1, y-2) && ISWAL(x+2, y-2)
   && ISBOX(x  , y-1) && ISN_S(x+1, y-1) && ISBOX(x+2, y-1)
      /*Current*/     && ISBOX(x+1, y  )
  ) return true;

  if (/*Current*/        ISBOX(x+1, y  )
   && ISBOX(x  , y+1) && ISN_S(x+1, y+1) && ISWAL(x+2, y+1)
                      && ISBOX(x+1, y+2) && ISWAL(x+2, y+2)
  ) return true;

  if (                   ISBOX(x-1, y  )    /*Current*/
   && ISBOX(x-2, y+1) && ISN_S(x-1, y+1) && ISBOX(x  , y+1)
   && ISWAL(x-2, y+2) && ISWAL(x-1, y+2)
  ) return true;

  // ?b#  Cb?  ?bC  ##?
  // b-#  b-b  #-b  b-b
  // Cb?  ?##  #b?  ?bC

  if (                   ISBOX(x+1, y-2) && ISWAL(x+2, y-2)
   && ISBOX(x  , y-1) && ISN_S(x+1, y-1) && ISWAL(x+2, y-1)
      /*Current*/     && ISBOX(x+1, y  )
  ) return true;

  if (/*Current*/        ISBOX(x+1, y  )
   && ISBOX(x  , y+1) && ISN_S(x+1, y+1) && ISBOX(x+2, y+1)
                      && ISWAL(x+1, y+2) && ISWAL(x+2, y+2)
  ) return true;

  if (                   ISBOX(x-1, y  )    /*Current*/
   && ISWAL(x-2, y+1) && ISN_S(x-1, y+1) && ISBOX(x  , y+1)
   && ISWAL(x-2, y+2) && ISBOX(x-1, y+2)
  ) return true;

  if (ISWAL(x-2, y-2) && ISWAL(x-1, y-2)
   && ISBOX(x-2, y-1) && ISN_S(x-1, y-1) && ISBOX(x  , y-1)
                      && ISBOX(x-1, y  )   /*Current*/
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check46(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // #b?  ?##  bC?  ?bb
  // #-b  C-b  b-#  b-C
  // ?Cb  bb?  ?b#  ##?

  if (ISWAL(x-1, y-2) && ISBOX(x  , y-2)
   && ISWAL(x-1, y-1) && ISN_S(x  , y-1) && ISBOX(x+1, y-1)
                         /*Current*/     && ISBOX(x+1, y  )
  ) return true;

  if (                   ISWAL(x+1, y-1) && ISWAL(x+2, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISBOX(x+2, y  )
   && ISBOX(x  , y+1) && ISBOX(x+1, y+1)
  ) return true;

  if (ISBOX(x-1, y  )    /*Current*/
   && ISBOX(x-1, y+1) && ISN_S(x  , y+1) && ISWAL(x+1, y+1)
                      && ISBOX(x  , y+2) && ISWAL(x+1, y+2)
  ) return true;

  if (                   ISBOX(x-1, y-1) && ISBOX(x  , y-1)
   && ISBOX(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
   && ISWAL(x-2, y+1) && ISWAL(x-1, y+1)
  ) return true;

  // ?b#  bb?  ?Cb  ##?
  // b-#  C-b  #-b  b-C
  // bC?  ?##  #b?  ?bb

  if (                   ISBOX(x  , y-2) && ISWAL(x+1, y-2)
   && ISBOX(x-1, y-1) && ISN_S(x  , y-1) && ISWAL(x+1, y-1)
   && ISBOX(x-1, y  )    /*Current*/
  ) return true;

  if (ISBOX(x  , y-1) && ISBOX(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISBOX(x+2, y  )
                      && ISWAL(x+1, y+1) && ISWAL(x+2, y+1)
  ) return true;

  if (                   /*Current*/        ISBOX(x+1, y  )
   && ISWAL(x-1, y+1) && ISN_S(x  , y+1) && ISBOX(x+1, y+1)
   && ISWAL(x-1, y+2) && ISBOX(x  , y+2)
  ) return true;

  if (ISWAL(x-2, y-1) && ISWAL(x-1, y-1)
   && ISBOX(x-2, y  ) && ISN_S(x-1, y  )   /*Current*/
                      && ISBOX(x-1, y+1) && ISBOX(x  , y+1)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check61(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // bb?  ?bb  bb?  ?Cb
  // b-C  b-b  C-b  b-b
  // ?bb  bC?  ?bb  bb?

  if (ISBOX(x-2, y-1) && ISBOX(x-1, y-1)
   && ISBOX(x-2, y  ) && ISN_S(x-1, y  )    /*Current*/
                      && ISBOX(x-1, y+1) && ISBOX(x  , y+1)
  ) return true;

  if (                   ISBOX(x  , y-2) && ISBOX(x+1, y-2)
   && ISBOX(x-1, y-1) && ISN_S(x  , y-1) && ISBOX(x+1, y-1)
   && ISBOX(x-1, y  )    /*Current*/
  ) return true;

  if (ISBOX(x  , y-1) && ISBOX(x+1, y-1)
      /*Current*/     && ISN_S(x+1, y  ) && ISBOX(x+2, y  )
                      && ISBOX(x+1, y+1) && ISBOX(x+2, y+1)
  ) return true;

  if (                   /*Current*/        ISBOX(x+1, y  )
   && ISBOX(x-1, y+1) && ISN_S(x  , y+1) && ISBOX(x+1, y+1)
   && ISBOX(x-1, y+2) && ISBOX(x  , y+2)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check62(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // Cb?  ?bC  bb?  ?bb
  // b-b  b-b  b-b  b-b
  // ?bb  bb?  ?bC  Cb?

  if (/*Current*/        ISBOX(x+1, y  )
   && ISBOX(x  , y+1) && ISN_S(x+1, y+1) && ISBOX(x+2, y+1)
                      && ISBOX(x+1, y+2) && ISBOX(x+2, y+2)
  ) return true;

  if (                   ISBOX(x-1, y  )    /*Current*/
   && ISBOX(x-2, y+1) && ISN_S(x-1, y+1) && ISBOX(x  , y+1)
   && ISBOX(x-2, y+2) && ISBOX(x-1, y+2)
  ) return true;

  if (ISBOX(x-2, y-2) && ISBOX(x-1, y-2)
   && ISBOX(x-2, y-1) && ISN_S(x-1, y-1) && ISBOX(x  , y-1)
                      && ISBOX(x-1, y  )    /*Current*/
  ) return true;

  if (                   ISBOX(x+1, y-2) && ISBOX(x+2, y-2)
   && ISBOX(x  , y-1) && ISN_S(x+1, y-1) && ISBOX(x+2, y-1)
      /*Current*/     && ISBOX(x+1, y  )
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check4001(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // ?###  ###?    b#  #C  
  // #.bC  bb.#    b#  #b  
  // #b      b#  Cb.#  #.bb
  // #b      C#  ###?  ?###

  if (                   ISWAL(x-2, y-1) && ISWAL(x-1, y-1) && ISWAL(x  , y-1)
   && ISWAL(x-3, y  ) && ISG_S(x-2, y  ) && ISBOX(x-1, y  )    /*Current*/
   && ISWAL(x-3, y+1) && ISBOX(x-2, y+1)
   && ISWAL(x-3, y+2) && ISBOX(x-2, y+2)
  ) return true;

  if (ISWAL(x-2, y-3) && ISWAL(x-1, y-3) && ISWAL(x  , y-3)
   && ISBOX(x-2, y-2) && ISBOX(x-1, y-2) && ISG_S(x  , y-2) && ISWAL(x+1, y-2)
                                         && ISBOX(x  , y-1) && ISWAL(x+1, y-1)
                                            /*Current*/     && ISWAL(x+1, y  )
  ) return true;

  if (                                      ISBOX(x+2, y-2) && ISWAL(x+3, y-2)
                                         && ISBOX(x+2, y-1) && ISWAL(x+3, y-1)
      /*Current*/     && ISBOX(x+1, y  ) && ISG_S(x+2, y  ) && ISWAL(x+3, y  )
   && ISWAL(x  , y+1) && ISWAL(x+1, y+1) && ISWAL(x+2, y+1)
  ) return true;

  if (ISWAL(x-1, y  )    /*Current*/
   && ISWAL(x-1, y+1) && ISBOX(x  , y+1)
   && ISWAL(x-1, y+2) && ISG_S(x  , y+2) && ISBOX(x+1, y+2) && ISBOX(x+2, y+2)
                      && ISWAL(x  , y+3) && ISWAL(x+1, y+3) && ISWAL(x+2, y+3)
  ) return true;

  // ?###  ###?    C#  #b  
  // #.bb  Cb.#    b#  #b  
  // #b      b#  bb.#  #.bC
  // #C      b#  ###?  ?###

  if (                   ISWAL(x  , y-3) && ISWAL(x+1, y-3) && ISWAL(x+2, y-3)
   && ISWAL(x-1, y-2) && ISG_S(x  , y-2) && ISBOX(x+1, y-2) && ISBOX(x+2, y-2)
   && ISWAL(x-1, y-1) && ISBOX(x  , y-1)
   && ISWAL(x-1, y  )    /*Current*/
  ) return true;

  if (ISWAL(x  , y-1) && ISWAL(x+1, y-1) && ISWAL(x+2, y-1)
      /*Current*/     && ISBOX(x+1, y  ) && ISG_S(x+2, y  ) && ISWAL(x+3, y  )
                                         && ISBOX(x+2, y+1) && ISWAL(x+3, y+1)
                                         && ISBOX(x+2, y+2) && ISWAL(x+3, y+2)
  ) return true;

  if (                                      /*Current*/        ISWAL(x+1, y  )
                                         && ISBOX(x  , y+1) && ISWAL(x+1, y+1)
   && ISBOX(x-2, y+2) && ISBOX(x-1, y+2) && ISG_S(x  , y+2) && ISWAL(x+1, y+2)
   && ISWAL(x-2, y+3) && ISWAL(x-1, y+3) && ISWAL(x  , y+3)
  ) return true;

  if (ISWAL(x-3, y-2) && ISBOX(x-2, y-2)
   && ISWAL(x-3, y-1) && ISBOX(x-2, y-1)
   && ISWAL(x-3, y  ) && ISG_S(x-2, y  ) && ISBOX(x-1, y  )  /*Current*/
                      && ISWAL(x-2, y+1) && ISWAL(x-1, y+1) && ISWAL(x  , y+1)
  ) return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool UnmovableFinder::Check4002(const Table& T, const GoalsHolder& G, const int x, const int y) {
  // ?###  ###?    b#  #b  
  // #.Cb  bb.#    b#  #C  
  // #b      C#  bC.#  #.bb
  // #b      b#  ###?  ?###

  if (                   ISWAL(x-1, y-1) && ISWAL(x  , y-1) && ISWAL(x+1, y-1)
   && ISWAL(x-2, y  ) && ISG_S(x-1, y  )    /*Current*/     && ISBOX(x+1, y  )
   && ISWAL(x-2, y+1) && ISBOX(x-1, y+1)
   && ISWAL(x-2, y+2) && ISBOX(x-1, y+2)
  ) return true;

  if (ISWAL(x-2, y-2) && ISWAL(x-1, y-2) && ISWAL(x  , y-2)
   && ISBOX(x-2, y-1) && ISBOX(x-1, y-1) && ISG_S(x  , y-1) && ISWAL(x+1, y-1)
                                            /*Current*/     && ISWAL(x+1, y  )
                                         && ISBOX(x  , y+1) && ISWAL(x+1, y+1)
  ) return true;

  if (                                      ISBOX(x+1, y-2) && ISWAL(x+2, y-2)
                                         && ISBOX(x+1, y-1) && ISWAL(x+2, y-1)
   && ISBOX(x-1, y  )    /*Current*/     && ISG_S(x+1, y  ) && ISWAL(x+2, y  )
   && ISWAL(x-1, y+1) && ISWAL(x  , y+1) && ISWAL(x+1, y+1)
  ) return true;

  if (ISWAL(x-1, y-1) && ISBOX(x  , y-1)
   && ISWAL(x-1, y  )    /*Current*/
   && ISWAL(x-1, y+1) && ISG_S(x  , y+1) && ISBOX(x+1, y+1) && ISBOX(x+2, y+1)
                      && ISWAL(x  , y+2) && ISWAL(x+1, y+2) && ISWAL(x+2, y+2)
  ) return true;

  // ?###  ###?    b#  #b  
  // #.bb  bC.#    C#  #b  
  // #C      b#  bb.#  #.Cb
  // #b      b#  ###?  ?###

  if (                   ISWAL(x  , y-2) && ISWAL(x+1, y-2) && ISWAL(x+2, y-2)
   && ISWAL(x-1, y-1) && ISG_S(x  , y-1) && ISBOX(x+1, y-1) && ISBOX(x+2, y-1)
   && ISWAL(x-1, y  )    /*Current*/
   && ISWAL(x-1, y+1) && ISBOX(x  , y+1)
  ) return true;

  if (ISWAL(x-1, y-1) && ISWAL(x  , y-1) && ISWAL(x+1, y-1)
   && ISBOX(x-1, y  )    /*Current*/     && ISG_S(x+1, y  ) && ISWAL(x+2, y  )
                                         && ISBOX(x+1, y+1) && ISWAL(x+2, y+1)
                                         && ISBOX(x+1, y+2) && ISWAL(x+2, y+2)
  ) return true;

  if (                                      ISBOX(x  , y-1) && ISWAL(x+1, y-1)
                                            /*Current*/     && ISWAL(x+1, y  )
   && ISBOX(x-2, y+1) && ISBOX(x-1, y+1) && ISG_S(x  , y+1) && ISWAL(x+1, y+1)
   && ISWAL(x-2, y+2) && ISWAL(x-1, y+2) && ISWAL(x  , y+2)
  ) return true;

  if (ISWAL(x-2, y-2) && ISBOX(x-1, y-2)
   && ISWAL(x-2, y-1) && ISBOX(x-1, y-1)
   && ISWAL(x-2, y  ) && ISG_S(x-1, y  )    /*Current*/     && ISBOX(x+1, y  )
                      && ISWAL(x-1, y+1) && ISWAL(x  , y+1) && ISWAL(x+1, y+1)
  ) return true;

  return false;
}
