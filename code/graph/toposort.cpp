#include <cstddef>
#include <vector>

// In solve: 1-based directed graph adj with n vertices.

std::vector<int> deg(n + 1), order;
for (int u = 1; u <= n; ++u) {
    for (int v : adj[u]) ++deg[v];
}
for (int u = 1; u <= n; ++u) {
    if (!deg[u]) order.push_back(u);
}
for (std::size_t i = 0; i < order.size(); ++i) {
    for (int v : adj[order[i]]) {
        if (--deg[v] == 0) order.push_back(v);
    }
}
bool acyclic = order.size() == static_cast<std::size_t>(n);
