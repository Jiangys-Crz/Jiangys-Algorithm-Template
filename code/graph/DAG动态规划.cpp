#include <algorithm>
#include <cstddef>
#include <limits>
#include <utility>
#include <vector>

using ll = long long;

// In solve: 1-based weighted adjacency list adj[u] of (v, w).
// n is the vertex count and s is the source.

constexpr ll negInf = -std::numeric_limits<ll>::max() / 4;
std::vector<ll> dp(n + 1, negInf);
dp[s] = 0;
std::vector<int> deg(n + 1), order;
for (int u = 1; u <= n; ++u) {
    for (const auto& edge : adj[u]) ++deg[edge.first];
}
for (int u = 1; u <= n; ++u) {
    if (!deg[u]) order.push_back(u);
}
for (std::size_t i = 0; i < order.size(); ++i) {
    int u = order[i];
    for (auto [v, w] : adj[u]) {
        if (dp[u] != negInf) dp[v] = std::max(dp[v], dp[u] + w);
        if (--deg[v] == 0) order.push_back(v);
    }
}
bool acyclic = order.size() == static_cast<std::size_t>(n);
// When acyclic, dp[u] is the longest distance; negInf means unreachable.
