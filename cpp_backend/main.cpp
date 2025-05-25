#include "graph.h"
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

void printPath(int node, const vector<int> &parent, ostream &out)
{
    if (parent[node] == -1)
    {
        out << node << " ";
        return;
    }
    printPath(parent[node], parent, out);
    out << node << " ";
}

int main()
{
    ifstream in("input.txt");
    if (!in)
    {
        cerr << "ERROR: Could not open input.txt\n";
        return 1;
    }

    int v, e, start, end;
    in >> v >> e; // First two lines: number of vertices and edges

    Graph g(v);

    // Read exactly 'e' edges
    int u, vertex, weight;
    for (int i = 0; i < e; i++)
    {
        in >> u >> vertex >> weight;
        g.addEdge(u, vertex, weight);
    }

    in >> start >> end;

    // Ensure that the start and end vertices are within the valid range
    if (start < 0 || start >= v || end < 0 || end >= v)
    {
        cerr << "ERROR: Invalid start or end vertex.\n";
        return 1;
    }

    // Initialize parent vector with -1
    vector<int> parent(v, -1);

    // Get the shortest distances from the source using Dijkstra's algorithm
    vector<int> dist = dijkstra(g, start, parent, v);

    // Check if there's a valid path to the destination
    if (dist[end] == INT_MAX)
    {
        cout << "No path from " << start << " to " << end << endl;
    }
    else
    {
        cout << "Shortest Distance from " << start << " to " << end << ": " << dist[end] << "\n";
        cout << "Path: ";
        printPath(end, parent, cout);
        cout << endl;
    }

    return 0;
}
