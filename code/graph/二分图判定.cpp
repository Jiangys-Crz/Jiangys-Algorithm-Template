#include <optional>

#include "graph.hpp"

std::optional<std::vector<int>> bipartiteColor(const Graph& g) {
    std::vector<int> color(g.n + 1, -1), q;
    for (int s = 1; s <= g.n; ++s) {
        if (color[s] != -1) continue;
        color[s] = 0;
        q.assign(1, s);
        for (std::size_t i = 0; i < q.size(); ++i) {
            int u = q[i];
            for (auto [v, id] : g.adj[u]) {
                if (color[v] == color[u]) return std::nullopt;
                if (color[v] != -1) continue;
                color[v] = color[u] ^ 1;
                q.push_back(v);
            }
        }
    }
    return color;
}
