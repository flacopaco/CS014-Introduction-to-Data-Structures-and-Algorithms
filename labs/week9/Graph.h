#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <climits>

#include "Vertex.h"

using namespace std;

class Graph {
private:
  vector<Vertex> vertices;
  void dfs_visit(Vertex &);
public:
  Graph();
  Graph(ifstream&);
  ~Graph();
  void output_graph(const string &);
  void bfs();
  void dfs();
};

#endif /* GRAPH_H_ */
