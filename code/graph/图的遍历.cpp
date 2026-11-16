#include <cstddef>
#include <utility>
#include <vector>

// In solve: 1-based adjacency list adj, n vertices, and start s.

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
