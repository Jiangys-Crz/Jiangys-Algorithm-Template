#include <algorithm>
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

std::optional<std::vector<int>> eulerTrail(const Graph& g) {
    if (!g.n) return std::nullopt;
    std::vector<int> deg(g.n + 1);
    for (auto [u, v, w] : g.edges) {
        ++deg[u];
        deg[v] += g.directed ? -1 : 1;
    }

    int start = g.edges.empty() ? 1 : g.edges.front().u;
    if (g.directed) {
        int plus = 0, minus = 0;
        for (int u = 1; u <= g.n; ++u) {
            if (deg[u] == 1) { start = u; ++plus; }
            else if (deg[u] == -1) ++minus;
            else if (deg[u]) return std::nullopt;
        }
        if (plus != minus || plus > 1) return std::nullopt;
    } else {
        int odd = 0;
        for (int u = 1; u <= g.n; ++u) {
            if (deg[u] % 2 == 0) continue;
            start = u;
            ++odd;
        }
        if (odd != 0 && odd != 2) return std::nullopt;
    }

    std::vector<char> used(g.edges.size());
    std::vector<std::size_t> cur(g.n + 1);
    std::vector<int> stk{start}, path;
    while (!stk.empty()) {
        int u = stk.back();
        auto& i = cur[u];
        while (i < g.adj[u].size() && used[g.adj[u][i].id]) ++i;
        if (i == g.adj[u].size()) {
            path.push_back(u);
            stk.pop_back();
        } else {
            auto [v, id] = g.adj[u][i++];
            used[id] = true;
            stk.push_back(v);
        }
    }
    if (path.size() != g.edges.size() + 1) return std::nullopt;
    std::reverse(path.begin(), path.end());
    return path;
}
