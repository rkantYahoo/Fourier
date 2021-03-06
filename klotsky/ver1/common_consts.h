#ifndef COMMON_CONSTS_H
#define COMMON_CONSTS_H

const int NUM_CELLS = 20;
const int ROWS = 5;
const int COLS = 4;
const int KINGS = 4;
const int BLANKS = 2;

enum Piece {
  KING,
  DHOR,
  DVER,
  SINGLETON,
  BLANK,
  ILLEGAL
};

enum Comparison {
  LT,
  EQ,
  GT
};

enum Direction {
  LEFT = -1,
  UP = -COLS,
  RIGHT = 1,
  DOWN = COLS
};

#endif
