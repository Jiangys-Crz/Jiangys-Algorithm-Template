#include <algorithm>

#include "graph.hpp"

std::vector<std::vector<ll>> floyd(const Graph& g) {
    std::vector<std::vector<ll>> dist(g.n + 1,
                                       std::vector<ll>(g.n + 1, graphInf));
    for (int u = 1; u <= g.n; ++u) dist[u][u] = 0;
    for (auto [u, v, w] : g.edges) {
        w = std::max(w, -graphInf);
        dist[u][v] = std::min(dist[u][v], w);
        if (!g.directed) dist[v][u] = std::min(dist[v][u], w);
    }
    for (int k = 1; k <= g.n; ++k) {
        for (int u = 1; u <= g.n; ++u) {
            if (dist[u][k] == graphInf) continue;
            for (int v = 1; v <= g.n; ++v) {
                if (dist[k][v] == graphInf) continue;
                ll nd = std::max(-graphInf, dist[u][k] + dist[k][v]);
                dist[u][v] = std::min(dist[u][v], nd);
            }
        }
    }
    return dist;
}
