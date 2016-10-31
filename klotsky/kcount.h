#ifndef KCOUNT_H
#define KCOUNT_H

using namespace std;

const int NUM_CELLS = 20;
const int ROWS = 5;
const int COLS = 4;
const int NUM_TWOS = 4;
const int NUM_ONES = 6;

class Board {
 public:
  Board();
  void NextBoard();
  const bool IsValidBoard() const;
  const bool IsLastBoard() const;
  void Print() const;

 private:
  const int CarryIndex() const;
  int config_[NUM_CELLS];
};

#endif
