#include <algorithm>
#include <cstddef>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

using ll = long long;

int main() {
    int n, m, s;
    if (!(std::cin >> n >> m >> s)) return 0;
    std::vector<std::vector<std::pair<int, ll>>> adj(n + 1);
    std::vector<int> deg(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        std::cin >> u >> v >> w;
        adj[u].push_back({v, w});
        ++deg[v];
    }

    constexpr ll negInf = -std::numeric_limits<ll>::max() / 4;
    std::vector<ll> dp(n + 1, negInf);
    dp[s] = 0;
    std::vector<int> order;
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
    if (static_cast<int>(order.size()) != n) {
        std::cout << "CYCLE\n";
        return 0;
    }

    for (int u = 1; u <= n; ++u) {
        if (dp[u] == negInf) std::cout << "NONE";
        else std::cout << dp[u];
        std::cout << (u == n ? '\n' : ' ');
    }
}
