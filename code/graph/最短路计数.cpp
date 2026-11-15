#include <algorithm>
#include <numeric>

#include "dijkstra.hpp"

std::vector<int> countShortestPaths(const Graph& g, int s) {
    constexpr int mod = 1000000007;
    auto dist = dijkstra(g, s);
    std::vector<int> ord(g.n), ways(g.n + 1);
    std::iota(ord.begin(), ord.end(), 1);
    std::sort(ord.begin(), ord.end(), [&](int u, int v) {
        return dist[u] < dist[v];
    });
    ways[s] = 1;
    for (int u : ord) {
        if (dist[u] == graphInf) break;
        for (auto [v, id] : g.adj[u]) {
            if (dist[v] != graphInf && g.edges[id].w == dist[v] - dist[u]) {
                ways[v] += ways[u];
                if (ways[v] >= mod) ways[v] -= mod;
            }
        }
    }
    return ways;
}
