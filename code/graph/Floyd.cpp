#include <algorithm>
#include <limits>
#include <vector>

using ll = long long;

// 先准备 n 个顶点及有向边 (u, v, w)，编号从 1 开始。
// 无向边按两个方向各存一次。

constexpr ll inf = numeric_limits<ll>::max() / 4;
vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, inf));
for (int u = 1; u <= n; ++u) dist[u][u] = 0;
for (auto [u, v, w] : edges) {
    dist[u][v] = min(dist[u][v], max(w, -inf));
}
for (int k = 1; k <= n; ++k) {
    for (int u = 1; u <= n; ++u) {
        if (dist[u][k] == inf) continue;
        for (int v = 1; v <= n; ++v) {
            if (dist[k][v] == inf) continue;
            ll nd = max(-inf, dist[u][k] + dist[k][v]);
            dist[u][v] = min(dist[u][v], nd);
        }
    }
}
