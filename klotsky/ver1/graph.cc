#include "graph.h"
#include <ctime>
#include <iostream>
#include <cmath>
#include <list>

using namespace std;

const int Kgraph::IndexOf(const Vertex& v,
			  int low, int high) const {

  if (low > high) {
    return -1;
  }

  //  std::cout << "Searching for " << low << " " << high;
  //  v.Print();

  int pivot = (low + high)/2;
  const Comparison c = vertices_[pivot].Compare(v);
  if (c == EQ) {
    return pivot;
  }
  if (c == LT) {
    return IndexOf(v, pivot + 1, high);
  }
  if (c == GT) {
    return IndexOf(v, low, pivot - 1);
  }
}

const int Kgraph::IndexOf(const Vertex& v) const {
  return IndexOf(v, 0, vertices_.size());
}

const int Kgraph::IndexAfterMove(const Vertex& v,
				 const int pivot,
				 const Direction D,
				 const int steps) const {
  Piece board[NUM_CELLS];
  v.CopyBoard(board);
  int new_pivot = pivot + D*steps;

  if (((steps == 2) && (D == LEFT) && ((pivot % COLS) == 1)) ||
      ((steps == 2) && (D == RIGHT) && ((pivot % COLS) == COLS - 2)) ||
      ((D == RIGHT) && ((pivot % COLS) == COLS - 1)) ||
      ((D == LEFT) && ((pivot % COLS) == 0))) {
    return -1;
  }

  if (v.PieceAt(pivot) == SINGLETON) {
    board[pivot] = BLANK;
    board[new_pivot] = SINGLETON;
  }

  if (v.PieceAt(pivot) == KING) {
    if (steps != 1) {
      return -1;
    }
    board[new_pivot] = board[new_pivot + 1] =
      board[new_pivot + COLS] = board[new_pivot + COLS + 1] = KING;

    int offset = 1;
    if ((D == LEFT) || (D == RIGHT)) {
      offset = COLS;
    }
    if (D > 0) {
      board[pivot] = board[pivot + offset] = BLANK;
    } else {
      board[pivot - D] = board[pivot - D + offset] = BLANK;
    }
  }

  if (v.PieceAt(pivot) == DHOR) {
    board[new_pivot] = board[new_pivot + 1] = DHOR;
    if (! ((steps == 1) && (D == LEFT))) {
      board[pivot] = BLANK;
    }
    if (! ((steps == 1) && (D == RIGHT))) {
      board[pivot + 1] = BLANK;
    }
  }

  if (v.PieceAt(pivot) == DVER) {
    board[new_pivot] = board[new_pivot + COLS] = DVER;
    if (! ((steps == 1) && (D == UP))) {
      board[pivot] = BLANK;
    }
    if (! ((steps == 1) && (D == DOWN))) {
      board[pivot + COLS] = BLANK;
    }
  }

  return IndexOf(Vertex(board)); 
}

const int Kgraph::Doffset(const Direction D) const {
  if (D > 0 ) {
    return -2*D;
  } else {
    return -D;
  }
}

const Direction Inv(const Direction D) {
  if (D == RIGHT) {
    return LEFT;
  }
  if (D == LEFT) {
    return RIGHT;
  }
  if (D == UP) {
    return DOWN;
  }
  if (D == DOWN) {
    return UP;
  }
}

void Kgraph::HandleMove(const int vindex, const int bindex, 
			const Direction D) {
  const Vertex& Vcurr = vertices_[vindex];
  Direction offset = RIGHT;
  if ((D == LEFT) || (D == RIGHT)) {
    offset = DOWN;
  }
  //  std::cout << "In HandleMove: " << bindex << " " << D;
  //  Vcurr.Print();

  if ((Vcurr.PieceAt(bindex - D) == KING) &&
      (Vcurr.PieceAt(bindex - D + offset) == KING) &&
      (Vcurr.PieceAt(bindex + offset) == BLANK)) {
    if (!vertices_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
						       bindex +
						       Doffset(D),
						       D, 1))) {
      //  std::cout << "Error in HandleMove King: " << vindex << "  "
      //		<< bindex << "  " << D << endl;
    }
  }

  if (Vcurr.PieceAt(bindex - D) == DHOR) {
    if (offset == 1) {
      if ((Vcurr.PieceAt(bindex - D + 1) == DHOR) &&
	  (Vcurr.PieceAt(bindex + 1) == BLANK)) {
	if (!vertices_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
							   bindex - D,
							   D, 1))) {
	  //  std::cout << "Error in HandleMove DHOR1: " << vindex << "  "
	  //	    << bindex << "  " << D << endl;
	}
      }
    } else {
      if (!vertices_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
							 bindex +
							 Doffset(D),
							 D, 1))) {
	// std::cout << "Error in HandleMove: DHOR2 " << vindex << "  "
	//	  << bindex << "  " << D << endl;
      }

      if ((Vcurr.PieceAt(bindex + D) == BLANK) &&
	  ((bindex % COLS) < COLS - 1) &&
	  ((bindex % COLS) > 0)) {
	if (!vertices_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
							   bindex +
							   Doffset(D),
							   D, 2))) {
	  // std::cout << "Error in HandleMove: DHOR3 " << vindex << "  "
	  //	    << bindex << "  " << D << endl;
	}
      }
    }
  }

  if (Vcurr.PieceAt(bindex - D) == DVER) {
    if (offset == COLS) {
      if ((Vcurr.PieceAt(bindex - D + COLS) == DVER) &&
	  (Vcurr.PieceAt(bindex + COLS) == BLANK)) {
	if (!vertices_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
							   bindex - D,
							   D, 1))) {
	  // std::cout << "Error in HandleMove: DVER1 " << vindex << "  "
	  //	    << bindex << "  " << D << endl;
	}
      }
    } else {
      if (!vertices_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
							 bindex +
							 Doffset(D),
							 D, 1))) {
	// std::cout << "Error in HandleMove: DVER2 " << vindex << "  "
	//	  << bindex << "  " << D << endl;
      }
      if (Vcurr.PieceAt(bindex + D) == BLANK) {
	if (!vertices_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
							   bindex +
							   Doffset(D),
							   D, 2))) {
	  // std::cout << "Error in HandleMove: DVER3 " << vindex << "  "
	  //	    << bindex << "  " << D << endl;
	}
      }
    }
  }

  if (Vcurr.PieceAt(bindex - D) == SINGLETON) {
    int neighbour = IndexAfterMove(Vcurr, bindex - D, D, 1);
    if (!vertices_[vindex].AddNeighbour(neighbour)) {
      // std::cout << "Error in HandleMove Singleton: " << vindex << "  "
      //		<< bindex << "  " << D << endl;
      // std::cout << "neighbour = " << neighbour << endl;
      // Vcurr.Print();
    }
    if (Vcurr.PieceAt(bindex + D) == BLANK) {
      if (!vertices_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
							 bindex - D,
							 D, 2))) {
	// std::cout << "Error in HandleMove Singleton: " << vindex << "  "
	//	  << bindex << "  " << D << endl;
      }
    }

    int new_index1 = bindex + offset;
    int new_index2 = bindex - offset;
  
    if ((new_index1 >= 0) && (new_index1 < NUM_CELLS) &&
	(Vcurr.PieceAt(new_index1) == BLANK)) {
      if (!vertices_[vindex].AddNeighbour(IndexAfterMove(vertices_[neighbour],
							 bindex, offset, 1))) {
	// std::cout << "Error in HandleMove Singleton: " << vindex << "  "
	//	  << bindex << "  " << D << endl;
      }
    }
    if ((new_index2 >= 0) && (new_index2 < NUM_CELLS) &&
	(Vcurr.PieceAt(new_index2) == BLANK)) {
      if (!vertices_[vindex].AddNeighbour(IndexAfterMove(vertices_[neighbour],
							 bindex, Inv(offset),
							 1))) {
	// std::cout << "Error in HandleMove Singleton: " << vindex << "  "
	//	  << bindex << "  " << D << endl;
      }
    }
  }
  //  std::cout << "Exiting handlemove " << Inv(offset) << endl;
}

Kgraph::Kgraph(Ken* InitK) {
  // Populate vertices in sorted order
  bool xit = false;
  num_positions_ = 0;

  do {
    ++num_positions_;
    if (InitK->IsValidBoard()) {
      //      Vertex(InitK->Board()).Print();
      vertices_.push_back(Vertex(InitK->Board()));
    }
    if (!InitK->IsLastBoard()) {
      InitK->NextBoard();
    } else {
      xit = true;
    }
  } while (!xit);

  time_taken_to_build_vertices_ = clock()/CLOCKS_PER_SEC;
  std::cout << "Num positions = " << num_positions_ << endl;
  std::cout << "time taken to build vertices = "
	    << time_taken_to_build_vertices_ << endl;

  //Populate the adjacency lists
  for (int a = 0; a < vertices_.size(); ++a) {
    for (int b = 0; b < BLANKS; ++b) {
      int bindex = vertices_[a].Blank(b);
      int x = bindex % COLS;
      int y = bindex / COLS;
      
      if (x > 0) {
	HandleMove(a, bindex, RIGHT);
      }
      
      if (x < COLS - 1) {
	HandleMove(a, bindex, LEFT);
      }
      
      if (y > 0) {
	HandleMove(a, bindex, DOWN);
      }
      
      if (y < ROWS - 1) {
	HandleMove(a, bindex, UP);
      }
    }
  }

  time_taken_to_build_graph_ = clock()/CLOCKS_PER_SEC;
  std::cout << "time taken to build graph = "
	    << time_taken_to_build_graph_ << endl;  
}

const int Kgraph::Size() const {
  return vertices_.size();
}

const Vertex& Kgraph::VertexAt(const int i) const {
  return vertices_[i];
}

void Kgraph::ComputeShortestPaths(const Vertex& source) {
  int source_index = IndexOf(source);

  if (source_index == -1) {
    std::cout << "Invalid Source\n";
    return;
  }

  list<int> q;

  for (int i = 0; i < vertices_.size(); ++i) {
    vertices_[i].SetWeight(-1);
  }

  vertices_[source_index].SetWeight(0);
  q.push_back(source_index);

  while (! (q.size() == 0)) {
    const int curr_index = q.front();
    q.pop_front();
    const Vertex& curr_v = vertices_[curr_index];
    

    const vector<int>& curr_adj = curr_v.AdjList();
    for (int i = 0; i < curr_adj.size(); ++i) {
      if (vertices_[curr_adj[i]].Weight() == -1) {
	vertices_[curr_adj[i]].SetWeight(curr_v.Weight() + 1);
	vertices_[curr_adj[i]].SetPrevVertex(curr_index);
	q.push_back(curr_adj[i]);
	if (vertices_[curr_adj[i]].IsDestination()) {
	  std::cout << "Length of shortest path = " << curr_v.Weight() << endl;
	  std::cout << "Total time taken = " << clock()/CLOCKS_PER_SEC << endl;
	  int current_index = curr_index;
	  while (current_index != source_index) {
	    std::cout << endl << current_index << ":";
	    vertices_[current_index].Print();
	    current_index = vertices_[current_index].PrevVertex();
	  }
	  std::cout << endl << source_index << ":";
	  vertices_[source_index].Print();
	  return;
	}
      }
    }
  }
}

int main() {
  Ken Klotski(2,8,4);
  Ken K18(0, 0, 14);
  Ken KDaisy(0, 4, 10);
  Ken KViolet(0, 6, 8);
  Ken KPoppy(2, 4, 8);
  Ken KPansy(0, 8, 6);
  Ken KSnowdrop(2, 6, 6);
  Ken KTrail(6, 4, 4);
  Ken KAmbush(6, 4, 4);

  Kgraph G(&KPansy);
  std::cout << "Size of Graph = " << G.Size() << endl;

  Piece source_board[NUM_CELLS] = {DVER, KING, KING, DVER,
				   DVER, KING, KING, DVER,
				   DVER, DHOR, DHOR, DVER,
				   DVER, SINGLETON, SINGLETON, DVER,
				   SINGLETON, BLANK, BLANK, SINGLETON};

  Piece source_18[NUM_CELLS] = {SINGLETON, KING, KING, SINGLETON,
				SINGLETON, KING, KING, SINGLETON,
				SINGLETON, SINGLETON, SINGLETON, SINGLETON,
				SINGLETON, SINGLETON, SINGLETON, SINGLETON,
				SINGLETON, BLANK, BLANK, SINGLETON};

  Piece source_daisy[NUM_CELLS] = {DVER, KING, KING, DVER,
				   DVER, KING, KING, DVER,
				   SINGLETON, SINGLETON, SINGLETON, SINGLETON,
				   SINGLETON, SINGLETON, SINGLETON, SINGLETON,
				   SINGLETON, BLANK, BLANK, SINGLETON};

  Piece source_violet[NUM_CELLS] = {DVER, KING, KING, DVER,
				    DVER, KING, KING, DVER,
				    DVER, SINGLETON, SINGLETON, SINGLETON,
				    DVER, SINGLETON, SINGLETON, SINGLETON,
				    SINGLETON, BLANK, BLANK, SINGLETON};

  Piece source_poppy[NUM_CELLS] = {DVER, KING, KING, DVER,
				   DVER, KING, KING, DVER,
				   SINGLETON, DHOR, DHOR, SINGLETON,
				   SINGLETON, SINGLETON, SINGLETON, SINGLETON,
				   SINGLETON, BLANK, BLANK, SINGLETON};

  Piece source_pansy[NUM_CELLS] = {DVER, KING, KING, DVER,
				   DVER, KING, KING, DVER,
				   DVER, SINGLETON, SINGLETON, DVER,
				   DVER, SINGLETON, SINGLETON, DVER,
				   SINGLETON, BLANK, BLANK, SINGLETON};

  Piece source_snowdrop[NUM_CELLS] = {DVER, KING, KING, DVER,
				      DVER, KING, KING, DVER,
				      DVER, DHOR, DHOR, SINGLETON,
				      DVER, SINGLETON, SINGLETON, SINGLETON,
				      SINGLETON, BLANK, BLANK, SINGLETON};

  Piece source_trail[NUM_CELLS] = {DVER, KING, KING, DVER,
				   DVER, KING, KING, DVER,
				   SINGLETON, DHOR, DHOR, SINGLETON,
				   SINGLETON, DHOR, DHOR, SINGLETON,
				   BLANK, DHOR, DHOR, BLANK};
  
  Piece source_ambush[NUM_CELLS] = {SINGLETON, KING, KING, SINGLETON,
				    DVER, KING, KING, DVER,
				    DVER, DHOR, DHOR, DVER,
				    SINGLETON, DHOR, DHOR, SINGLETON,
				    BLANK, DHOR, DHOR, BLANK};

  G.ComputeShortestPaths(Vertex(source_pansy));

  return 0;
}
