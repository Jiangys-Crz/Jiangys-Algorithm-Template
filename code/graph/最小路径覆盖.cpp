#include "bipartite_matching.hpp"
#include "toposort.hpp"

std::optional<std::vector<std::vector<int>>> minimumPathCover(const Graph& g) {
    if (!topologicalSort(g)) return std::nullopt;

    BipartiteMatching bm(g.n, g.n);
    for (auto [u, v, w] : g.edges) bm.addEdge(u, v);
    bm.work();
    std::vector<int> next(g.n + 1);
    for (int v = 1; v <= g.n; ++v) {
        if (bm.match[v]) next[bm.match[v]] = v;
    }

    std::vector<std::vector<int>> paths;
    for (int u = 1; u <= g.n; ++u) {
        if (bm.match[u]) continue;
        auto& path = paths.emplace_back();
        for (int v = u; v; v = next[v]) path.push_back(v);
    }
    return paths;
}
