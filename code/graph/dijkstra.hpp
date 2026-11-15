#pragma once

#include <functional>
#include <queue>
#include <utility>

#include "graph.hpp"

inline std::vector<ll> dijkstra(const Graph& g,
                                 const std::vector<int>& sources) {
    using State = std::pair<ll, int>;
    std::priority_queue<State, std::vector<State>, std::greater<>> pq;
    std::vector<ll> dist(g.n + 1, graphInf);
    for (int s : sources) {
        if (dist[s] == 0) continue;
        dist[s] = 0;
        pq.push({0, s});
    }
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, id] : g.adj[u]) {
            ll w = g.edges[id].w;
            if (w >= graphInf - d) continue;
            ll nd = d + w;
            if (nd >= dist[v]) continue;
            dist[v] = nd;
            pq.push({nd, v});
        }
    }
    return dist;
}

inline std::vector<ll> dijkstra(const Graph& g, int s) {
    return dijkstra(g, std::vector<int>{s});
}
