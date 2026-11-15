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

struct UnicyclicInfo {
    std::vector<int> cycle, bel, dist;
};

UnicyclicInfo decomposeUnicyclic(const Graph& g) {
    std::vector<int> deg(g.n + 1), q;
    for (int u = 1; u <= g.n; ++u) {
        deg[u] = static_cast<int>(g.adj[u].size());
        if (deg[u] == 1) q.push_back(u);
    }
    for (std::size_t i = 0; i < q.size(); ++i) {
        int u = q[i];
        deg[u] = 0;
        for (auto [v, id] : g.adj[u]) {
            if (deg[v] && --deg[v] == 1) q.push_back(v);
        }
    }

    UnicyclicInfo res{{}, std::vector<int>(g.n + 1),
                         std::vector<int>(g.n + 1)};
    for (int u = 1; u <= g.n; ++u) {
        if (!deg[u]) continue;
        res.cycle.push_back(u);
        res.bel[u] = u;
    }

    for (std::size_t i = q.size(); i > 0; --i) {
        int u = q[i - 1];
        for (auto [v, id] : g.adj[u]) {
            if (!res.bel[v]) continue;
            res.bel[u] = res.bel[v];
            res.dist[u] = res.dist[v] + 1;
            break;
        }
    }
    return res;
}
