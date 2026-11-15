#include <cstddef>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using ll = long long;

#ifndef XCPC_GRAPH_GRAPH_HPP
#define XCPC_GRAPH_GRAPH_HPP

inline constexpr ll graphInf = std::numeric_limits<ll>::max() / 4;

struct Graph {
    struct Edge {
        int u, v;
        ll w;
    };
    struct Arc {
        int v, id;
    };

    int n;
    bool directed;
    std::vector<Edge> edges;
    std::vector<std::vector<Arc>> adj;

    explicit Graph(int n, bool directed = true)
        : n(n), directed(directed), adj(n + 1) {}

    int addEdge(int u, int v, ll w = 1) {
        int id = static_cast<int>(edges.size());
        edges.push_back({u, v, w});
        adj[u].push_back({v, id});
        if (!directed) adj[v].push_back({u, id});
        return id;
    }
};

#endif

#ifndef XCPC_GRAPH_DIJKSTRA_HPP
#define XCPC_GRAPH_DIJKSTRA_HPP

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

#endif
