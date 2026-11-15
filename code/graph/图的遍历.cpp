#include <utility>

#include "graph.hpp"

std::vector<int> dfsOrder(const Graph& g, int s) {
    std::vector<char> vis(g.n + 1);
    std::vector<int> order{s};
    std::vector<std::pair<int, std::size_t>> stk{{s, 0}};
    vis[s] = true;

    while (!stk.empty()) {
        auto& [u, j] = stk.back();
        if (j == g.adj[u].size()) {
            stk.pop_back();
            continue;
        }
        int v = g.adj[u][j++].v;
        if (vis[v]) continue;
        vis[v] = true;
        order.push_back(v);
        stk.push_back({v, 0});
    }
    return order;
}

std::vector<int> bfsDistance(const Graph& g, int s) {
    std::vector<int> dist(g.n + 1, -1);
    std::vector<int> q{s};
    dist[s] = 0;
    for (std::size_t i = 0; i < q.size(); ++i) {
        int u = q[i];
        for (auto [v, id] : g.adj[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            q.push_back(v);
        }
    }
    return dist;
}
