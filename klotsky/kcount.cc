#include <iostream>
#include <ctime>
#include <set>
#include "kcount.h"

using namespace std;

Board::Board() {
  for (int a = 0; a < NUM_CELLS; ++a) {
    config_[a] = 0;
  }
}

const int Board::CarryIndex() const {
  int index = NUM_CELLS - 1;

  while ((config_[index] == 2) && (index > 0)) {
    --index;
  }

  return index;
}

void Board::NextBoard() {
  int index = CarryIndex();

  if (index == 5) {
    std::cout << "done ";
    std::cout << clock()/CLOCKS_PER_SEC << endl;
  }
  
  config_[index]++;
  for (int a = index + 1; a < NUM_CELLS; ++a) {
    config_[a] = 0;
  }
}

const bool Board::IsLastBoard() const {
  for (int a = 0; a < NUM_CELLS; ++a) {
    if (config_[a] != 2) {
      return false;
    }
  }

  return true;
}

void Board::Print() const {
  for (int a = 0; a < NUM_CELLS; ++a) {
    if ((a % COLS) == 0) {
      std::cout << endl;
    }
    std::cout << config_[a];
  }
  std::cout << endl;
}

const bool Board::IsValidBoard() const {
  int counters[3] = {0, 0, 0};
  int twos[4] = {0, 0, 0, 0};
  int ones[6] = {0, 0, 0, 0, 0, 0};
  
  for (int a = 0; a < NUM_CELLS; ++a) {
    counters[config_[a]]++;

    if (config_[a] == 2) {
      if (counters[2] > NUM_TWOS) {
	return false;
      }
      
      twos[counters[2] - 1] = a;
    }

    if (config_[a] == 1) {
      if (counters[1] > NUM_ONES) {
	return false;
      }
 
      ones[counters[1] - 1] = a;
    }
  }

  if ((counters[1] != NUM_ONES) || (counters[2] != NUM_TWOS)) {
    return false;
  }
  /*
  std::cout << twos[0] << twos[1] << twos[2] << twos[3] << endl;
  std::cout << ones[0] << ones[1] << ones[2] << ones[3]
	    << ones[4] << ones[5] << endl;
	    std::cout << counters[0] << "  " << counters[1] << "  " << counters[2] << endl;*/
  
  if (((twos[1] - twos[0]) != 1) ||
      ((twos[2] - twos[0]) != COLS) ||
      ((twos[3] - twos[1]) != COLS)) {
    return false;
  }

  set<int> visited;
  for (int b = 0; b < NUM_ONES; ++b) {
    set<int>::iterator ones_indices = visited.find(ones[b]);
    if (ones_indices == visited.end()) {
      visited.insert(ones[b]);
      visited.insert(ones[b] + COLS);
      //      std::cout << "inserted " << ones[b] << ones[b] + COLS << endl;
    }
  }
  if (visited.size() != NUM_ONES) {
    //    std::cout << "ones problem " << visited.size() << endl;
    return false;
  }
  
  return true;
}



int main() {
  Board b;
  int count = 0;

  while (!b.IsLastBoard()) {
    if (b.IsValidBoard()) {
      // b.Print();
      ++count;
    }
    b.NextBoard();
  }

  int time_taken = clock()/CLOCKS_PER_SEC;
  std::cout << "total count = " << count << endl;
  std::cout << "time taken = " << time_taken << endl;

  return 0;
}


