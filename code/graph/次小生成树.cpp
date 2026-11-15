#include "kruskal.hpp"
#include "path_max.hpp"

std::optional<ll> strictSecondMST(const Graph& g) {
    auto mst = kruskal(g);
    if (!mst) return std::nullopt;

    Graph tr(g.n, false);
    std::vector<char> used(g.edges.size());
    for (int id : mst->edges) {
        auto [u, v, w] = g.edges[id];
        tr.addEdge(u, v, w);
        used[id] = true;
    }

    TreePathMax path(tr);
    std::optional<lll> ans;
    for (std::size_t id = 0; id < g.edges.size(); ++id) {
        auto [u, v, w] = g.edges[id];
        if (used[id] || u == v) continue;
        auto [first, second] = path.query(u, v);
        auto removed = first && w == *first ? second : first;
        if (!removed) continue;
        lll weight = lll(mst->weight) + w - *removed;
        if (!ans || weight < *ans) ans = weight;
    }
    if (!ans) return std::nullopt;
    return static_cast<ll>(*ans);
}
