#include "vertex.h"
#include <cassert>
#include <iostream>

using namespace std;

Vertex::Vertex(const Piece* P) {
  bool king_found = false;
  for (int a = 0, sindex = 0, bindex = 0; a < NUM_CELLS; ++a) {
    board_[a] = P[a];
    if (P[a] != KING) {
      sboard_[sindex] = P[a];
      sindices_[sindex++] = a;
    } else if (! king_found) {
      king_position_ = a;
      king_found = true;
    }

    if (P[a] == BLANK) {
      bindices_[bindex++] = a;
    }
  }
}

Vertex::Vertex(const Ken* K) {
  const Piece* B = K->Board();
  const Piece* SB = K->SBoard();
  for (int a = 0; a < NUM_CELLS; ++a) {
    board_[a] = B[a];
  }
  for (int a = 0; a < NUM_CELLS - KINGS; ++a) {
    sboard_[a] = SB[a];
  }
  king_position_ = K->KingPosition();
}

const Piece* Vertex::SBoard() const {
  return sboard_;
}

const int Vertex::KingPosition() const {
  return king_position_;
}

const int Vertex::Blank(const int i) const {
  if (i == 0) {
    return bindices_[0];
  }

  return bindices_[1];
}

const Piece Vertex::PieceAt(int i) const {
  if ((i < 0) || (i >= NUM_CELLS)) {
    //    std::cout << "Error at PieceAt: " << i << endl;
    return ILLEGAL;
  }

  assert((i >= 0) && (i < NUM_CELLS));
  return board_[i];
}

void Vertex::CopyBoard(Piece* P) const {
  for (int i = 0; i < NUM_CELLS; ++i) {
    P[i] = board_[i];
  }
}

const bool Vertex::AddNeighbour(const int i) {
  if (i == -1) {
    //    std::cout << "Illegal Neighbour\n";
    return false;
  }
  adj_list_.push_back(i);
  return true;
}

const Comparison Vertex::Compare(const Vertex& Q) const {
  /*  std::cout << "comparing";
  Print();
  std::cout << king_position_ << "and" << endl;
  Q.Print();
  std::cout << Q.KingPosition() << endl; */

  if (king_position_ < Q.KingPosition()) {
    return LT;
  }

  if (king_position_ > Q.KingPosition()) {
    return GT;
  }

  const Piece* Qsb = Q.SBoard();
  int index = 0;
  while (index < NUM_CELLS - KINGS) {
    if (sboard_[index] < Qsb[index]) {
      return LT;
    }
    if (sboard_[index] > Qsb[index]) {
      return GT;
    }
    ++index;
  }

  return EQ;
}

void Vertex::Print() const {
  for (int a = 0; a < NUM_CELLS; ++a) {
    if ((a % COLS) == 0) {
      std::cout << endl;
    }
    std::cout << board_[a];
  }
  std::cout << endl << "Weight = " << weight_ << endl;
  for (int a = 0; a < adj_list_.size(); ++a) {
    std::cout << adj_list_[a] << " ";
  }
  std::cout << endl;
  std::cout << "Prev Vertex = " << prev_vertex_ << endl;
}  

const vector<int>& Vertex::AdjList() const {
  return adj_list_;
}

const bool Vertex::IsDestination() const {
  if (king_position_ == NUM_CELLS - 2*COLS) {
    return true;
  } else {
    return false;
  }
}

const int Vertex::Weight() const {
  return weight_;
}

const int Vertex::PrevVertex() const {
  return prev_vertex_;
}

void Vertex::SetWeight(const int w) {
  weight_ = w;
}

void Vertex::SetPrevVertex(const int p) {
  prev_vertex_ = p;
}
