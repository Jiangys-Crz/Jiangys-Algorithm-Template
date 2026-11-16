#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using ll = long long;

int main() {
    int n, m, k;
    if (!(std::cin >> n >> m >> k)) return 0;
    std::vector<std::vector<std::pair<int, ll>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        std::cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    constexpr ll inf = std::numeric_limits<ll>::max() / 4;
    std::vector<ll> dist(n + 1, inf);

    using State = std::pair<ll, int>;
    std::priority_queue<State, std::vector<State>, std::greater<>> pq;
    for (int i = 0; i < k; ++i) {
        int s;
        std::cin >> s;
        if (dist[s] == 0) continue;
        dist[s] = 0;
        pq.push({0, s});
    }
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (w >= inf - d) continue;
            ll nd = d + w;
            if (nd >= dist[v]) continue;
            dist[v] = nd;
            pq.push({nd, v});
        }
    }

    for (int u = 1; u <= n; ++u) {
        if (dist[u] == inf) std::cout << "INF";
        else std::cout << dist[u];
        std::cout << (u == n ? '\n' : ' ');
    }
}
