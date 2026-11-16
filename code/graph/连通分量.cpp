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

    std::vector<int> bel(n + 1), stk;
    int cnt = 0;
    for (int s = 1; s <= n; ++s) {
        if (bel[s]) continue;
        bel[s] = ++cnt;
        stk.push_back(s);
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            for (int v : adj[u]) {
                if (bel[v]) continue;
                bel[v] = cnt;
                stk.push_back(v);
            }
        }
    }
    std::cout << cnt << '\n';
    for (int u = 1; u <= n; ++u) {
        std::cout << bel[u] << (u == n ? '\n' : ' ');
    }
}
