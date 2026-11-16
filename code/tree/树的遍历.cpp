#include <cstddef>
#include <iostream>
#include <vector>

int main() {
    int n, root;
    if (!(std::cin >> n >> root)) return 0;
    std::vector<std::vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> fa(n + 1), stk{root};
    while (!stk.empty()) {
        int u = stk.back();
        stk.pop_back();
        std::cout << u << ' ';
        for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it) {
            int v = *it;
            if (v == fa[u]) continue;
            fa[v] = u;
            stk.push_back(v);
        }
    }
    std::cout << '\n';

    std::vector<int> dep(n + 1), q{root};
    for (std::size_t i = 0; i < q.size(); ++i) {
        int u = q[i];
        for (int v : adj[u]) {
            if (v == fa[u]) continue;
            dep[v] = dep[u] + 1;
            q.push_back(v);
        }
    }
    for (int u : q) std::cout << u << ' ';
    std::cout << '\n';
    for (int u = 1; u <= n; ++u) {
        std::cout << dep[u] << (u == n ? '\n' : ' ');
    }
}
