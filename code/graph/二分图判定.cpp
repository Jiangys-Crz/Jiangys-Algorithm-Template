#include <cstddef>
#include <limits>
#include <optional>
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

std::optional<std::vector<int>> bipartiteColor(const Graph& g) {
    std::vector<int> color(g.n + 1, -1), q;
    for (int s = 1; s <= g.n; ++s) {
        if (color[s] != -1) continue;
        color[s] = 0;
        q.assign(1, s);
        for (std::size_t i = 0; i < q.size(); ++i) {
            int u = q[i];
            for (auto [v, id] : g.adj[u]) {
                if (color[v] == color[u]) return std::nullopt;
                if (color[v] != -1) continue;
                color[v] = color[u] ^ 1;
                q.push_back(v);
            }
        }
    }
    return color;
}
