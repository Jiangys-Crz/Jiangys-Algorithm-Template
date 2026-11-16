#include <queue>
#include <vector>

// In solve: 0-based unweighted adjacency list graph and a valid start vertex.

std::vector<int> dist(graph.size(), -1);
std::queue<int> q;
dist[start] = 0;
q.push(start);
while (!q.empty()) {
    int v = q.front();
    q.pop();
    // TODO: Process v or record predecessors when discovering neighbors.
    for (int u : graph[v]) {
        if (dist[u] == -1) {
            dist[u] = dist[v] + 1;
            q.push(u);
        }
    }
}
