#include <deque>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

using ll = long long;

int main() {
    int n, m, s;
    if (!(std::cin >> n >> m >> s)) return 0;
    std::vector<std::vector<std::pair<int, ll>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        std::cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    constexpr ll inf = std::numeric_limits<ll>::max() / 4;
    std::vector<ll> dist(n + 1, inf);

    std::deque<std::pair<ll, int>> q{{0, s}};
    dist[s] = 0;
    while (!q.empty()) {
        auto [d, u] = q.front();
        q.pop_front();
        if (d != dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            ll nd = d + w;
            if (nd >= dist[v]) continue;
            dist[v] = nd;
            if (w == 0) q.push_front({nd, v});
            else q.push_back({nd, v});
        }
    }

    for (int u = 1; u <= n; ++u) {
        if (dist[u] == inf) std::cout << "INF";
        else std::cout << dist[u];
        std::cout << (u == n ? '\n' : ' ');
    }
}
