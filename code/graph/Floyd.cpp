#include <algorithm>
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

std::vector<std::vector<ll>> floyd(const Graph& g) {
    std::vector<std::vector<ll>> dist(g.n + 1,
                                       std::vector<ll>(g.n + 1, graphInf));
    for (int u = 1; u <= g.n; ++u) dist[u][u] = 0;
    for (auto [u, v, w] : g.edges) {
        w = std::max(w, -graphInf);
        dist[u][v] = std::min(dist[u][v], w);
        if (!g.directed) dist[v][u] = std::min(dist[v][u], w);
    }
    for (int k = 1; k <= g.n; ++k) {
        for (int u = 1; u <= g.n; ++u) {
            if (dist[u][k] == graphInf) continue;
            for (int v = 1; v <= g.n; ++v) {
                if (dist[k][v] == graphInf) continue;
                ll nd = std::max(-graphInf, dist[u][k] + dist[k][v]);
                dist[u][v] = std::min(dist[u][v], nd);
            }
        }
    }
    return dist;
}
