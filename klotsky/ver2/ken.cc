#include <cassert>
#include <ctime>
#include <iostream>
#include <list>
#include <set>
#include "ken.h"

using namespace std;

Ken::Ken(int dhors, int dvers, int singletons)
  : dhors_(dhors),
    dvers_(dvers),
    singletons_(singletons) {
  assert(dhors >= 0);
  assert(dvers >= 0);
  assert(singletons >= 0);
  assert((dhors + dvers + singletons) ==
	 NUM_CELLS - KINGS - BLANKS);

  board_[0] = board_[1] =
    board_[COLS] = board_[COLS + 1] = KING;
  king_position_ = 0;

  for (int a = 2, index = 0; a < NUM_CELLS; ++a) {
    if ((a == COLS) || (a == COLS + 1)) {
      continue;
    }

    sindices_[index] = a;
    if (index < dhors) {
      sboard_[index++] = board_[a] = DHOR;
    } else if (index < dhors + dvers) {
      sboard_[index++] = board_[a] = DVER;
    } else if (index < dhors + dvers + singletons) {
      sboard_[index++] = board_[a] = SINGLETON;
    } else {
      sboard_[index++] = board_[a] = BLANK;
    }
  }
}
    
void Ken::Print() const {
  for (int a = 0; a < NUM_CELLS; ++a) {
    if ((a % COLS) == 0) {
      std::cout << endl;
    }
    std::cout << board_[a];
  }
  std::cout << endl;
}

void Ken::SPrint() const {
  int sindex = 0;
  for (int a = 0; a < NUM_CELLS; ++a) {
    if ((a % COLS) == 0) {
      std::cout << endl;
    }

    if (sindices_[sindex] == a) {
      std::cout << sboard_[sindex++];
    } else {
      std::cout << "X";
    }
  }
  std::cout << endl;
}

void Ken::FillBoardUsingS() {
  for (int a = 0, sindex = 0; a < NUM_CELLS; ++a) {
    if (sindices_[sindex] == a) {
      board_[a] = sboard_[sindex++];
    } else {
      board_[a] = KING;
    }
  }
}

bool Ken::AdvanceTheKing() {
  int x = king_position_ % COLS,
    y= king_position_/COLS;

  if (x < COLS - 2) {
    ++king_position_;
  } else if (y < ROWS - 1) {
    king_position_ += 2;
  } else {
    return false;
  }

  for (int a = 0, index = 0; a < NUM_CELLS; ++a) {
    if ((a != king_position_) && (a != king_position_ + 1) &&
	(a != king_position_ + COLS) &&
	(a != king_position_ + COLS + 1)) {
      sindices_[index++] = a;
    }
  }

  return true;
}

void Ken::NextBoard() {
  list<Piece> sorted_ssuffix;
  sorted_ssuffix.push_back(sboard_[NUM_CELLS - KINGS - 1]);
  int index;

  for (index = NUM_CELLS - KINGS - 2;
       (sboard_[index] >= sboard_[index + 1]) && index >= 0;
       --index) {
    sorted_ssuffix.push_back(sboard_[index]);
  }

  list<Piece>::iterator ssuffix_it = sorted_ssuffix.begin();
  if (index == -1) {
    for (int a = 0; ssuffix_it != sorted_ssuffix.end();
	 ++a, ++ssuffix_it){
      sboard_[a] = *ssuffix_it;
    }

    if (!AdvanceTheKing()) {
      return;
    }
    FillBoardUsingS();
    return;
  }

  Piece element_to_be_inserted = sboard_[index];
  bool found_replacement = false;
  for (int a = index + 1;
       (a < NUM_CELLS - KINGS) &&
	 (ssuffix_it != sorted_ssuffix.end());
       ++a, ++ssuffix_it) {
    if ((*ssuffix_it > element_to_be_inserted) &&
	!found_replacement) {
      found_replacement = true;
      sboard_[index] = *ssuffix_it;
      sboard_[a] = element_to_be_inserted;
    } else {
      sboard_[a] = *ssuffix_it;
    }
  }

  FillBoardUsingS();
}


const bool Ken::IsValidBoard() const {
  set<int> Kings, Dhors, Dvers;

  for (int index = 0; index < NUM_CELLS; ++index) {
    if (board_[index] == KING) {
      if (Kings.size() == 0) {
	if ((index % COLS) == COLS - 1) {
	  return false;
	}
	if ((index/COLS) >= ROWS - 1) {
	  return false;
	}
	Kings.insert(index);
	Kings.insert(index + 1);
	Kings.insert(index + COLS);
	Kings.insert(index + COLS + 1);
      } else {
	set<int>::iterator kindex = Kings.find(index);
	if (kindex == Kings.end()) {
	  return false;
	}
      }
    }

    if (board_[index] == DHOR) {
      set<int>::iterator hindex = Dhors.find(index);
      if (hindex == Dhors.end()) {
	if ((index % COLS) == COLS - 1) {
	  return false;
	}
	Dhors.insert(index);
	Dhors.insert(index + 1);
      }
    }

    if (board_[index] == DVER) {
      set<int>::iterator vindex = Dvers.find(index);
      if (vindex == Dvers.end()) {
	Dvers.insert(index);
	Dvers.insert(index + COLS);
      }
    }
  }

  if (!((Kings.size() == KINGS) && (Dhors.size() == dhors_) &&
	(Dvers.size() == dvers_))) {
    return false;
  }

  return true;
}

const bool Ken::IsLastBoard() const {
  if (king_position_ < NUM_CELLS - COLS - 2) {
    return false;
  }
  for (int a = 0; a < NUM_CELLS - KINGS - 1; ++a) {
    if (sboard_[a] < sboard_[a + 1]) {
      return false;
    }
  }

  return true;
}

const int Ken::KingPosition() const {
  return king_position_;
}

const Piece* Ken::Board() const {
  return board_;
}

const Piece* Ken::SBoard() const {
  return sboard_;
}
/*
int main() {
  Ken Klotski(2,8,4);
  std::cout << "Initial board: ";
  Klotski.Print();
  std::cout << "Sboard: ";
  Klotski.SPrint();

  int count = 0;
  while (!Klotski.IsLastBoard()) {
    if (Klotski.IsValidBoard()) {
      ++count;
    }
    Klotski.NextBoard();
  }
  if (Klotski.IsValidBoard()) {
    ++count;
  }

  int time_taken = clock()/CLOCKS_PER_SEC;
  std::cout << "Number of valid boards = " << count << endl;
  std::cout << "Time taken = " << time_taken << " seconds\n";

  return 0;
}
*/
