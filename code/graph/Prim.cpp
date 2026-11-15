#include <functional>
#include <queue>
#include <tuple>

#include "kruskal.hpp"

std::optional<MSTResult> prim(const Graph& g, int s = 1) {
    if (!g.n) return std::nullopt;
    using State = std::tuple<ll, int, int>;
    std::priority_queue<State, std::vector<State>, std::greater<>> pq;
    std::vector<char> vis(g.n + 1);
    MSTResult res;
    lll weight = 0;
    pq.push({0, -1, s});
    while (!pq.empty()) {
        auto [w, id, u] = pq.top();
        pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        if (id != -1) {
            weight += w;
            res.edges.push_back(id);
        }
        for (auto [v, e] : g.adj[u]) {
            if (!vis[v]) pq.push({g.edges[e].w, e, v});
        }
    }
    if (static_cast<int>(res.edges.size()) != g.n - 1) return std::nullopt;
    res.weight = static_cast<ll>(weight);
    return res;
}
