#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    int n, m, s;
    if (!(std::cin >> n >> m >> s)) return 0;
    std::vector<std::vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
    }

    std::vector<char> vis(n + 1);
    std::vector<int> order{s};
    std::vector<std::pair<int, std::size_t>> stk{{s, 0}};
    vis[s] = true;
    while (!stk.empty()) {
        auto& [u, j] = stk.back();
        if (j == adj[u].size()) {
            stk.pop_back();
            continue;
        }
        int v = adj[u][j++];
        if (vis[v]) continue;
        vis[v] = true;
        order.push_back(v);
        stk.push_back({v, 0});
    }

    std::vector<int> dist(n + 1, -1), q{s};
    dist[s] = 0;
    for (std::size_t i = 0; i < q.size(); ++i) {
        int u = q[i];
        for (int v : adj[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            q.push_back(v);
        }
    }

    for (int u : order) std::cout << u << ' ';
    std::cout << '\n';
    for (int u = 1; u <= n; ++u) {
        std::cout << dist[u] << (u == n ? '\n' : ' ');
    }
}
