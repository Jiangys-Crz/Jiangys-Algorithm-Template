#include <iostream>
#include <queue>
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

    std::vector<int> dist(graph.size(), -1);
    std::queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : graph[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    for (int x : dist) std::cout << x << ' ';
    std::cout << '\n';
}
