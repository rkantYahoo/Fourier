void Kgraph::HandleMove(const int vindex, const int bindex, 
			const Direction D) {
  const Vertex& Vcurr = vertices_[vindex];
  Direction offset = RIGHT;
  if ((D == LEFT) || (D == RIGHT)) {
    offset = DOWN;
  }

  if ((Vcurr.PieceAt(bindex - D) == KING) &&
      (Vcurr.PieceAt(bindex - D + offset) == KING) &&
      (Vcurr.PieceAt(bindex + offset) == BLANK)) {
    vertices_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
						  bindex +
						  Doffset(D),
						  D, 1));
  }

  if (Vcurr.PieceAt(bindex - D) == DHOR) {
    if ((offset == 1) &&
	(Vcurr.PieceAt(bindex - D + 1) == DHOR) &&
	(Vcurr.PieceAt(bindex + 1) == BLANK)) {
      vertices_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
						    bindex - D,
						    D, 1));
    } else {
      vertices_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
						    bindex +
						    Doffset(D),
						    D, 1));
      if (Vcurr.PieceAt(bindex + D) == BLANK) {
	vertices_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
						      bindex +
						      Doffset(D),
						      D, 2));
      }
    }
  }

  if (Vcurr.PieceAt(bindex - D) == DVER) {
    if ((offset == COLS) &&
	(Vcurr.PieceAt(bindex - D + COLS) == DVER) &&
	(Vcurr.PieceAt(bindex + COLS) == BLANK)) {
      vertex_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
						  bindex - D,
						  D, 1));
    } else {
      vertex_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
						  bindex +
						  Doffset(D),
						  D, 1));
      if (Vcurr.PieceAt(bindex + D) == BLANK) {
	vertices_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
						      bindex +
						      Doffset(D),
						      D, 2));
      }
    }
  }

  if (Vcurr.PieceAt(bindex - D) == SINGLETON) {
    int neighbour = IndexAfterMove(Vcurr, bindex - D, D, 1);
    vertices_[vindex].AddNeighbour(neighbour);
    if (Vcurr.PieceAt(bindex + D) == BLANK) {
      vertices_[vindex].AddNeighbour(IndexAfterMove(Vcurr,
						    bindex - D,
						    D, 2));
    }

    int new_index1 = bindex + offset;
    int new_index2 = bindex - offset;
  
    if ((new_index1 >=0) && (new_index1 < NUM_CELLS) &&
	(Vcurr.PieceAt(new_index1) == BLANK)) {
      vertices_[vindex].AddNeighbour(IndexAfterMove(vertices_[neighbour],
						    bindex, offset, 1));
    }
    if ((new_index2 >=0) && (new_index2 < NUM_CELLS) &&
	(Vcurr.PieceAt(new_index2) == BLANK)) {
      vertices_[vindex].AddNeighbour(IndexAfterMove(vertices_[neighbour],
						    bindex, -offset, 1));
    }
  }
}

const int Kgraph::Doffset(const Direction D) {
  if (D > 0 ) {
    return -2*D;
  } else {
    return -D;
  }
}
