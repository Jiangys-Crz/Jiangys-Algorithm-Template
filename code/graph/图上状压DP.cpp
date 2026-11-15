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

std::optional<ll> shortestHamiltonianPath(const Graph& g, int s, int t) {
    unsigned states = 1u << g.n;
    std::vector<ll> dp(static_cast<std::size_t>(states) * g.n, graphInf);
    auto at = [&](unsigned mask, int u) -> ll& {
        return dp[static_cast<std::size_t>(mask) * g.n + u - 1];
    };
    auto bit = [](int u) { return 1u << (u - 1); };
    at(bit(s), s) = 0;

    for (unsigned mask = bit(s); mask < states; ++mask) {
        for (int u = 1; u <= g.n; ++u) {
            if (at(mask, u) == graphInf) continue;
            for (auto [v, id] : g.adj[u]) {
                if (mask & bit(v)) continue;
                auto& dest = at(mask | bit(v), v);
                dest = std::min(dest, at(mask, u) + g.edges[id].w);
            }
        }
    }
    ll ans = at(states - 1, t);
    if (ans == graphInf) return std::nullopt;
    return ans;
}
