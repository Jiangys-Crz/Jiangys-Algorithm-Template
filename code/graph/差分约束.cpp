#include <optional>

#include "bellman_ford.hpp"

struct DifferenceConstraints {
    int n;
    Graph g;

    explicit DifferenceConstraints(int n) : n(n), g(n + 1) {
        for (int u = 1; u <= n; ++u) g.addEdge(n + 1, u, 0);
    }

    // x[u] - x[v] <= w
    void add(int u, int v, ll w) {
        g.addEdge(v, u, w);
    }

    std::optional<std::vector<ll>> work() const {
        auto res = bellmanFord(g, n + 1);
        if (res.negativeCycle) return std::nullopt;
        res.dist.pop_back();
        return res.dist;
    }
};
