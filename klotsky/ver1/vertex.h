#ifndef VERTEX_H
#define VERTEX_H

#include "common_consts.h"
#include "ken.h"
#include <vector>

using namespace std;

class Vertex {
 public:
  Vertex(const Piece* P);
  Vertex(const Ken* K);
  const Piece PieceAt(int i) const;
  const bool IsAdjacent(const Vertex& Q) const;
  const Comparison Compare(const Vertex& Q) const;
  const Piece* Board() const;
  const Piece* SBoard() const;
  void CopyBoard(Piece* p) const;
  const bool IsDestination() const;
  const int KingPosition() const;
  const int Blank(const int i) const;
  const bool AddNeighbour(const int i);
  const int Weight() const;
  void SetWeight(const int w);
  const int PrevVertex() const;
  void SetPrevVertex(const int p);

  void Print() const;
  const vector<int>& AdjList() const;

 private:
  Piece board_[NUM_CELLS];
  Piece sboard_[NUM_CELLS - KINGS];
  int sindices_[NUM_CELLS - KINGS];
  int bindices_[BLANKS];
  int king_position_;
  int weight_;
  int prev_vertex_;

  vector<int> adj_list_;
};

#endif
