#ifndef KBOARD_H
#define KBOARD_H

using namespace std;

const int NUM_CELLS = 20;
const int ROWS = 5;
const int COLS = 4;

class KBoardCounter {
 public:
  KBoardCounter(int dhor, int dver);
  void NextBoard();
  const bool IsValidBoard() const;
  const bool IsLastBoard() const;
  void Print() const;

 private:
  const int CarryIndex() const;
  int config_[NUM_CELLS - 4];
  int dhor_;
  int dver_;
};

#endif
