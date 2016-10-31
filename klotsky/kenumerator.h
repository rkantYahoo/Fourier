#ifndef KENUMERATOR_H
#define KENUMERATOR_H

using namespace std;

const int NUM_CELLS = 20;
const int ROWS = 5;
const int COLS = 4;

enum Piece {
  BLANK,
  KING,
  DHOR,
  DVER,
  SINGLETON
};

class KEnumerator {
 public:
  KEnumerator(int blanks,
	      int kings,
	      int dhors,
	      int dvers,
	      int singletons);
  void NextBoard();
  const bool IsValidBoard() const;
  const bool IsLastBoard() const;
  void Print() const;

 private:
  Piece board_[NUM_CELLS];
  int blanks_;
  int kings_;
  int dhors_;
  int dvers_;
  int singletons_;
};

#endif
