#include "graph.hpp"

Graph freeEdgeLayers(const Graph& g, int k) {
    Graph layer((k + 1) * g.n);
    auto id = [&](int u, int used) { return used * g.n + u; };
    for (int used = 0; used <= k; ++used) {
        for (int u = 1; u <= g.n; ++u) {
            for (auto [v, e] : g.adj[u]) {
                layer.addEdge(id(u, used), id(v, used), g.edges[e].w);
                if (used < k) layer.addEdge(id(u, used), id(v, used + 1), 0);
            }
        }
    }
    return layer;
}
