#include <vector>

std::vector<int> dfsOrder(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<char> visited(graph.size(), false);
    std::vector<int> order;
    auto dfs = [&](auto&& self, int v) -> void {
        visited[v] = true;
        order.push_back(v);
        for (int u : graph[v]) {
            if (!visited[u]) {
                self(self, u);
            }
        }
    };
    dfs(dfs, start);
    return order;
}
