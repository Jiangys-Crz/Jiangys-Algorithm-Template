#include <algorithm>
#include <optional>

#include "graph.hpp"

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
