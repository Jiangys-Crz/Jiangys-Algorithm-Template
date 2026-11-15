#include <deque>
#include <utility>

#include "graph.hpp"

std::vector<ll> zeroOneBfs(const Graph& g, int s) {
    std::vector<ll> dist(g.n + 1, graphInf);
    std::deque<std::pair<ll, int>> q{{0, s}};
    dist[s] = 0;
    while (!q.empty()) {
        auto [d, u] = q.front();
        q.pop_front();
        if (d != dist[u]) continue;
        for (auto [v, id] : g.adj[u]) {
            ll w = g.edges[id].w;
            if (d + w >= dist[v]) continue;
            dist[v] = d + w;
            if (!w) q.push_front({dist[v], v});
            else q.push_back({dist[v], v});
        }
    }
    return dist;
}
