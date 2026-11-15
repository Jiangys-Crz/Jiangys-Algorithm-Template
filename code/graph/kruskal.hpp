#pragma once

#include <algorithm>
#include <numeric>
#include <optional>

#include "graph.hpp"
#include "graph_dsu.hpp"

struct MSTResult {
    ll weight = 0;
    std::vector<int> edges;
};

inline std::optional<MSTResult> kruskal(const Graph& g) {
    std::vector<int> ord(g.edges.size());
    std::iota(ord.begin(), ord.end(), 0);
    std::sort(ord.begin(), ord.end(), [&](int x, int y) {
        return g.edges[x].w < g.edges[y].w;
    });
    GraphDSU dsu(g.n);
    MSTResult res;
    lll weight = 0;
    for (int id : ord) {
        auto [u, v, w] = g.edges[id];
        if (!dsu.merge(u, v)) continue;
        weight += w;
        res.edges.push_back(id);
        if (static_cast<int>(res.edges.size()) == g.n - 1) break;
    }
    if (static_cast<int>(res.edges.size()) != g.n - 1) return std::nullopt;
    res.weight = static_cast<ll>(weight);
    return res;
}
