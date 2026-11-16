#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using ll = long long;

int main() {
    int n, m;
    if (!(std::cin >> n >> m)) return 0;
    constexpr ll inf = std::numeric_limits<ll>::max() / 4;
    std::vector<std::vector<ll>> dist(n + 1, std::vector<ll>(n + 1, inf));
    for (int u = 1; u <= n; ++u) dist[u][u] = 0;
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        std::cin >> u >> v >> w;
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

    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            if (dist[u][v] == inf) std::cout << "INF";
            else std::cout << dist[u][v];
            std::cout << (v == n ? '\n' : ' ');
        }
    }
}
