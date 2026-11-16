#include <vector>

// In solve: 0-based adjacency list graph and a valid start vertex.

std::vector<char> visited(graph.size(), false);
std::vector<int> order;
auto dfs = [&](auto&& self, int v) -> void {
    visited[v] = true;
    order.push_back(v);
    // TODO: Process v on entry if needed.
    for (int u : graph[v]) {
        if (!visited[u]) {
            self(self, u);
        }
    }
};
dfs(dfs, start);
