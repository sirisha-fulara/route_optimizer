// dijkstra.h
#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <vector>
#include "graph.h"

std::vector<int> dijkstra(Graph &g, int src, std::vector<int> &parent, int V);
void printPath(int dest, std::vector<int> &parent);
#endif
