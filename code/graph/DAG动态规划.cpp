#include <algorithm>

#include "toposort.hpp"

std::optional<std::vector<ll>> dagLongestPath(const Graph& g, int s) {
    auto order = topologicalSort(g);
    if (!order) return std::nullopt;

    std::vector<ll> dp(g.n + 1, -graphInf);
    dp[s] = 0;
    for (int u : *order) {
        if (dp[u] == -graphInf) continue;
        for (auto [v, id] : g.adj[u]) {
            dp[v] = std::max(dp[v], dp[u] + g.edges[id].w);
        }
    }
    return dp;
}
