#include "graph.h"
#include <queue>
#include <climits>

vector<int> dijkstra(Graph &g, int src, vector<int> &parent, int V) {
    vector<int> dist(V, INT_MAX);
    parent.assign(V, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto &neighbour : g.adjList[u]) {
            int v = neighbour.first;
            int weight = neighbour.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                std::cout << "Updated parent of " << v << " to " << u << std::endl;  // Debugging

                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}


void printPath(int dest, vector<int> &parent){
    if (parent[dest] == -1)
    {
        cout << dest << " ";
        return;
    }
    printPath(parent[dest], parent);
    cout << dest << " ";
}
