#include <cstddef>
#include <iostream>
#include <vector>

int main() {
    int n, m;
    if (!(std::cin >> n >> m)) return 0;
    std::vector<std::vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> color(n + 1, -1), q;
    for (int s = 1; s <= n; ++s) {
        if (color[s] != -1) continue;
        color[s] = 0;
        q.assign(1, s);
        for (std::size_t i = 0; i < q.size(); ++i) {
            int u = q[i];
            for (int v : adj[u]) {
                if (color[v] == color[u]) {
                    std::cout << "NO\n";
                    return 0;
                }
                if (color[v] != -1) continue;
                color[v] = color[u] ^ 1;
                q.push_back(v);
            }
        }
    }
    std::cout << "YES\n";
    for (int u = 1; u <= n; ++u) {
        std::cout << color[u] << (u == n ? '\n' : ' ');
    }
}
