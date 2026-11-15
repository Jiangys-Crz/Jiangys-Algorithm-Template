#include "graph_dsu.hpp"
#include "toposort.hpp"

bool hasCycle(const Graph& g) {
    if (g.directed) return !topologicalSort(g).has_value();

    GraphDSU dsu(g.n);
    for (auto [u, v, w] : g.edges) {
        if (!dsu.merge(u, v)) return true;
    }
    return false;
}
