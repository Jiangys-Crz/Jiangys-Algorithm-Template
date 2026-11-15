#include <cstddef>
#include <deque>
#include <limits>
#include <utility>
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

std::vector<ll> zeroOneBfs(const Graph& g, int s) {
    std::vector<ll> dist(g.n + 1, graphInf);
    std::deque<std::pair<ll, int>> q{{0, s}};
    dist[s] = 0;
    while (!q.empty()) {
        auto [d, u] = q.front();
        q.pop_front();
        if (d != dist[u]) continue;
        for (auto [v, id] : g.adj[u]) {
            ll w = g.edges[id].w;
            if (d + w >= dist[v]) continue;
            dist[v] = d + w;
            if (!w) q.push_front({dist[v], v});
            else q.push_back({dist[v], v});
        }
    }
    return dist;
}
