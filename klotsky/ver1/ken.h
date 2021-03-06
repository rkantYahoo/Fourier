#ifndef KEN_H
#define KEN_H

#include "common_consts.h"

using namespace std;

class Ken {
 public:
  Ken(int dhors, int dvers, int singletons);
  void NextBoard();

  const bool IsValidBoard() const;
  const bool IsLastBoard() const;

  void Print() const;
  void SPrint() const;

  const int KingPosition() const;
  const Piece* Board() const;
  const Piece* SBoard() const;

 private:
  void FillBoardUsingS();
  bool AdvanceTheKing();

  Piece board_[NUM_CELLS];
  Piece sboard_[NUM_CELLS - KINGS];
  int sindices_[NUM_CELLS - KINGS];
  int king_position_;
  int dhors_;
  int dvers_;
  int singletons_;
};

#endif
