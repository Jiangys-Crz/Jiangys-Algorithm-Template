#include <cstddef>
#include <iostream>
#include <vector>

int main() {
    int n, m;
    if (!(std::cin >> n >> m)) return 0;
    std::vector<std::vector<int>> adj(n + 1);
    std::vector<int> deg(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        ++deg[v];
    }

    std::vector<int> order;
    for (int u = 1; u <= n; ++u) {
        if (!deg[u]) order.push_back(u);
    }
    for (std::size_t i = 0; i < order.size(); ++i) {
        for (int v : adj[order[i]]) {
            if (--deg[v] == 0) order.push_back(v);
        }
    }

    if (static_cast<int>(order.size()) != n) {
        std::cout << "CYCLE\n";
    } else {
        for (int u : order) std::cout << u << ' ';
        std::cout << '\n';
    }
}
