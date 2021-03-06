#ifndef GRAPH_H
#define GRAPH_H

#include "ken.h"
#include "vertex.h"

using namespace std;

class Kgraph {
 public:
  Kgraph(Ken* InitK);
  const int IndexOf(const Vertex& v,
		    int low_index,
		    int high_index) const;
  const int IndexOf(const Vertex& v) const;
  const int Size() const;
  const Vertex& VertexAt(const int i) const;
  void FillComponents();
  void ComputeShortestPaths(const Vertex& source);

 private:
  const int IndexAfterMove(const Vertex& v,
			   const int pivot,
			   const Direction D,
			   const int steps) const;

  const int Doffset(const Direction D) const;
  void HandleMove(const int vindex,
		  const int bindex,
		  const Direction D);

  vector<Vertex> vertices_;
  int num_positions_;
  int time_taken_to_build_vertices_;
  int time_taken_to_build_graph_;

  vector<int> components_[100];
};

#endif
