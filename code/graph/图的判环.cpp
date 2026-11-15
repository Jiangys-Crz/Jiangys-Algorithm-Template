#include <cstddef>
#include <limits>
#include <numeric>
#include <optional>
#include <utility>
#include <vector>

using ll = long long;

#ifndef XCPC_GRAPH_GRAPH_DSU_HPP
#define XCPC_GRAPH_GRAPH_DSU_HPP

struct GraphDSU {
    std::vector<int> fa, siz;

    explicit GraphDSU(int n) : fa(n + 1), siz(n + 1, 1) {
        std::iota(fa.begin(), fa.end(), 0);
    }

    int find(int u) {
        while (u != fa[u]) {
            fa[u] = fa[fa[u]];
            u = fa[u];
        }
        return u;
    }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (siz[u] < siz[v]) std::swap(u, v);
        fa[v] = u;
        siz[u] += siz[v];
        return true;
    }
};

#endif

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

#ifndef XCPC_GRAPH_TOPOSORT_HPP
#define XCPC_GRAPH_TOPOSORT_HPP

inline std::optional<std::vector<int>> topologicalSort(const Graph& g) {
    std::vector<int> deg(g.n + 1), order;
    for (auto [u, v, w] : g.edges) ++deg[v];
    for (int u = 1; u <= g.n; ++u) {
        if (!deg[u]) order.push_back(u);
    }
    for (std::size_t i = 0; i < order.size(); ++i) {
        int u = order[i];
        for (auto [v, id] : g.adj[u]) {
            if (--deg[v] == 0) order.push_back(v);
        }
    }
    if (static_cast<int>(order.size()) != g.n) return std::nullopt;
    return order;
}

#endif

bool hasCycle(const Graph& g) {
    if (g.directed) return !topologicalSort(g).has_value();

    GraphDSU dsu(g.n);
    for (auto [u, v, w] : g.edges) {
        if (!dsu.merge(u, v)) return true;
    }
    return false;
}
