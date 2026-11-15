#include <cstddef>
#include <limits>
#include <vector>

using ll = long long;

#ifndef XCPC_GRAPH_GRAPH_HPP
#define XCPC_GRAPH_GRAPH_HPP

inline constexpr ll graphInf = std::numeric_limits<ll>::max() / 4;

struct Graph {
    struct Edge {
        int u, v;
        ll w;
    };
    struct Arc {
        int v, id;
    };

    int n;
    bool directed;
    std::vector<Edge> edges;
    std::vector<std::vector<Arc>> adj;

    explicit Graph(int n, bool directed = true)
        : n(n), directed(directed), adj(n + 1) {}

    int addEdge(int u, int v, ll w = 1) {
        int id = static_cast<int>(edges.size());
        edges.push_back({u, v, w});
        adj[u].push_back({v, id});
        if (!directed) adj[v].push_back({u, id});
        return id;
    }
};

#endif

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
