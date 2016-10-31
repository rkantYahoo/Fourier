#include <cassert>
#include <ctime>
#include <iostream>
#include <list>
#include <set>
#include "kenumerator.h"

using namespace std;

KEnumerator::KEnumerator(int blanks,
			 int kings,
			 int dhors,
			 int dvers,
			 int singletons)
  : blanks_(blanks),
    kings_(kings),
    dhors_(dhors),
    dvers_(dvers),
    singletons_(singletons) {
  assert((blanks + kings + dhors + dvers + singletons) == NUM_CELLS);
  
  int counter = 0;
  
  for (int b = 0; b < blanks; ++b, ++counter) {
    board_[counter] = BLANK;
  }
  
  for (int k = 0; k < kings; ++k, ++counter) {
    board_[counter] = KING;
  }
  
  for (int h = 0; h < dhors; ++h, ++counter) {
    board_[counter] = DHOR;
  }
  
  for (int v = 0; v < dvers; ++v, ++counter) {
    board_[counter] = DVER;
  }
  
  for (int s = 0; s < singletons; ++s, ++counter) {
    board_[counter] = SINGLETON;
  }
}

const bool KEnumerator::IsValidBoard() const {
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

  if (!((Kings.size() == kings_) && (Dhors.size() == dhors_) &&
	(Dvers.size() == dvers_))) {
    return false;
  }

  return true;
}

void KEnumerator::NextBoard() {
  list<Piece> sorted_suffix;
  sorted_suffix.push_back(board_[NUM_CELLS - 1]);
  int index;

  for (index = NUM_CELLS - 2;
       (board_[index] >= board_[index + 1]) && index >= 0;
       --index) {
    sorted_suffix.push_back(board_[index]);
  }

  if (index == -1) {
    return;
  }

  if (index == 3) {
    // Print();
    std::cout << "Time taken = " << clock()/CLOCKS_PER_SEC << endl;
  }

  // At this point board_[index] < board_[index + 1] and index >= 0

  Piece element_to_be_inserted = board_[index];
  bool found_replacement = false;

  list<Piece>::iterator suffix_it = sorted_suffix.begin();
  for (int a = index + 1;
       (a < NUM_CELLS) && (suffix_it != sorted_suffix.end());
       ++a, ++suffix_it) {
    if ((*suffix_it > element_to_be_inserted) && !found_replacement) {
      found_replacement = true;
      board_[index] = *suffix_it;
      board_[a] = element_to_be_inserted;
    } else {
      board_[a] = *suffix_it;
    }
  }   
}

const bool KEnumerator::IsLastBoard() const {
  for (int index = 0; index < NUM_CELLS - 1; ++index) {
    if (board_[index] < board_[index + 1]) {
      return false;
    }
  }

  return true;
}

void KEnumerator::Print() const {
  for (int a = 0; a < NUM_CELLS; ++a) {
    if ((a % COLS) == 0) {
      std::cout << endl;
    }
    std::cout << board_[a];
  }
  std::cout << endl;
}

int main() {
  KEnumerator Klotsky(6, 4, 2, 8, 0);
  int count = 0;
  while (!Klotsky.IsLastBoard()) {
    if (Klotsky.IsValidBoard()) {
      ++count;
      if ((count % 100) == 0) {
      	std::cout << count << endl;
	Klotsky.Print();
      }
    }
    Klotsky.NextBoard();
  }

  int time_taken = clock()/CLOCKS_PER_SEC;
  std::cout << "Time taken = " << time_taken << endl;
  std::cout << "number of valid boards = " << count << endl;
  return 0;
}
