#include <iostream>
#include <vector>

int main() {
    int n, m, start;
    if (!(std::cin >> n >> m >> start)) return 0;
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
    }

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
    for (int x : order) std::cout << x << ' ';
    std::cout << '\n';
}
