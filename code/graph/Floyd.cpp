#include <algorithm>
#include <limits>
#include <vector>

using ll = long long;

// In solve: int n and directed edges (u, v, w), numbered 1..n.
// Add both directions for undirected edges.

constexpr ll inf = std::numeric_limits<ll>::max() / 4;
std::vector<std::vector<ll>> dist(n + 1, std::vector<ll>(n + 1, inf));
for (int u = 1; u <= n; ++u) dist[u][u] = 0;
for (auto [u, v, w] : edges) {
    dist[u][v] = std::min(dist[u][v], std::max(w, -inf));
}
for (int k = 1; k <= n; ++k) {
    for (int u = 1; u <= n; ++u) {
        if (dist[u][k] == inf) continue;
        for (int v = 1; v <= n; ++v) {
            if (dist[k][v] == inf) continue;
            ll nd = std::max(-inf, dist[u][k] + dist[k][v]);
            dist[u][v] = std::min(dist[u][v], nd);
        }
    }
}
