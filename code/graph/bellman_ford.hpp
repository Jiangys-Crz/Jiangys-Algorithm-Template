#pragma once

#include "graph.hpp"

struct RelaxResult {
    std::vector<ll> dist;
    bool negativeCycle = false;
};

namespace graph_detail {
inline constexpr lll wideInf = lll{1} << 126;

inline RelaxResult finishRelaxation(const std::vector<lll>& d, bool cycle) {
    RelaxResult res{std::vector<ll>(d.size()), cycle};
    for (std::size_t u = 0; u < d.size(); ++u) {
        if (d[u] >= graphInf) res.dist[u] = graphInf;
        else if (d[u] < -graphInf) res.dist[u] = -graphInf;
        else res.dist[u] = static_cast<ll>(d[u]);
    }
    return res;
}
}

inline RelaxResult bellmanFord(const Graph& g, int s) {
    std::vector<lll> d(g.n + 1, graph_detail::wideInf);
    d[s] = 0;
    auto relax = [&](int u, int v, ll w) {
        if (d[u] == graph_detail::wideInf || d[u] + w >= d[v]) return false;
        d[v] = d[u] + w;
        return true;
    };
    for (int i = 1; i <= g.n; ++i) {
        bool changed = false;
        for (auto [u, v, w] : g.edges) {
            changed |= relax(u, v, w);
            if (!g.directed) changed |= relax(v, u, w);
        }
        if (!changed) return graph_detail::finishRelaxation(d, false);
    }
    return graph_detail::finishRelaxation(d, true);
}
