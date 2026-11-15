#include <algorithm>
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

struct DegeneracyColoring {
    int degeneracy = 0;
    std::vector<int> color;
};

DegeneracyColoring greedyColoring(const Graph& g) {
    using State = std::pair<int, int>;
    std::priority_queue<State, std::vector<State>, std::greater<>> pq;
    std::vector<int> deg(g.n + 1), order;
    std::vector<char> removed(g.n + 1);
    for (int u = 1; u <= g.n; ++u) {
        deg[u] = static_cast<int>(g.adj[u].size());
        pq.push({deg[u], u});
    }

    DegeneracyColoring res{0, std::vector<int>(g.n + 1)};
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (removed[u] || d != deg[u]) continue;
        removed[u] = true;
        order.push_back(u);
        res.degeneracy = std::max(res.degeneracy, d);
        for (auto [v, id] : g.adj[u]) {
            if (!removed[v]) pq.push({--deg[v], v});
        }
    }

    std::vector<int> seen(g.n + 1);
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        int u = *it, c = 1;
        for (auto [v, id] : g.adj[u]) seen[res.color[v]] = u;
        while (seen[c] == u) ++c;
        res.color[u] = c;
    }
    return res;
}
