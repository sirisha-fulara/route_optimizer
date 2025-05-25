#include "graph.h"
#include "dijkstra.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h> 
#include <mutex>

namespace py = pybind11;
PYBIND11_MODULE(route_optimizer, m)
{
    py::class_<Graph>(m, "Graph").def(py::init<int>()).def("addEdge", &Graph::addEdge);
     m.def("Dijkstra", [](Graph &g, int src, int V) {
        std::vector<int> parent;
        std::vector<int> dist = dijkstra(g, src, parent, V);
        return py::make_tuple(dist, parent);  // ✅ Returning both vectors
    });
}