#include "graph.h"

Graph::Graph(int v) {
    // No internal state yet; maybe use if needed later
}

void Graph::addEdge(int u, int v, int weight) {
    adjList[u].push_back(make_pair(v, weight));
    adjList[v].push_back(make_pair(u, weight));
}
