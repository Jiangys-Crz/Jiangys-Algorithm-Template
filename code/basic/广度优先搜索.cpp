#include <queue>
#include <vector>

std::vector<int> bfsDistances(const std::vector<std::vector<int>>& graph, int start) {
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
    return dist;
}
