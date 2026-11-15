#include <cstddef>
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

std::vector<int> dfsOrder(const Graph& g, int s) {
    std::vector<char> vis(g.n + 1);
    std::vector<int> order{s};
    std::vector<std::pair<int, std::size_t>> stk{{s, 0}};
    vis[s] = true;

    while (!stk.empty()) {
        auto& [u, j] = stk.back();
        if (j == g.adj[u].size()) {
            stk.pop_back();
            continue;
        }
        int v = g.adj[u][j++].v;
        if (vis[v]) continue;
        vis[v] = true;
        order.push_back(v);
        stk.push_back({v, 0});
    }
    return order;
}

std::vector<int> bfsDistance(const Graph& g, int s) {
    std::vector<int> dist(g.n + 1, -1);
    std::vector<int> q{s};
    dist[s] = 0;
    for (std::size_t i = 0; i < q.size(); ++i) {
        int u = q[i];
        for (auto [v, id] : g.adj[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            q.push_back(v);
        }
    }
    return dist;
}
