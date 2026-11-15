#pragma once

#include <optional>

#include "graph.hpp"

inline std::optional<std::vector<int>> topologicalSort(const Graph& g) {
    std::vector<int> deg(g.n + 1), order;
    for (auto [u, v, w] : g.edges) ++deg[v];
    for (int u = 1; u <= g.n; ++u) {
        if (!deg[u]) order.push_back(u);
    }
    for (std::size_t i = 0; i < order.size(); ++i) {
        int u = order[i];
        for (auto [v, id] : g.adj[u]) {
            if (--deg[v] == 0) order.push_back(v);
        }
    }
    if (static_cast<int>(order.size()) != g.n) return std::nullopt;
    return order;
}
