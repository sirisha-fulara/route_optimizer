// graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

class Graph {
public:
    map<int, list<pair<int, int>>> adjList;
    Graph(int v); // constructor declaration
    void addEdge(int u, int v, int weight);
};

vector<int> dijkstra(Graph &g, int src, vector<int>& parent, int v); // function declaration
void printPath(int dest, vector<int>& parent);                // function declaration

#endif
