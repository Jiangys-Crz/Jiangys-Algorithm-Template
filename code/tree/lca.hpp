#pragma once

#include "../types.hpp"
#include "tree.hpp"

struct LCA {
    std::vector<int> dep;
    std::vector<std::vector<int>> up;

    explicit LCA(const Tree& tr) : dep(tr.dep), up{tr.fa} {
        for (ll step = 2; step <= tr.n; step *= 2) {
            const auto& prev = up.back();
            std::vector<int> next(tr.n + 1);
            for (int u = 1; u <= tr.n; ++u) next[u] = prev[prev[u]];
            up.push_back(std::move(next));
        }
    }

    int jump(int u, int k) const {
        if (k > dep[u]) return 0;
        for (int j = 0; k; ++j, k >>= 1) {
            if (k & 1) u = up[j][u];
        }
        return u;
    }

    int lca(int u, int v) const {
        if (dep[u] < dep[v]) std::swap(u, v);
        u = jump(u, dep[u] - dep[v]);
        if (u == v) return u;
        for (int j = static_cast<int>(up.size()) - 1; j >= 0; --j) {
            if (up[j][u] != up[j][v]) {
                u = up[j][u];
                v = up[j][v];
            }
        }
        return up[0][u];
    }

    int dist(int u, int v) const {
        int p = lca(u, v);
        return (dep[u] - dep[p]) + (dep[v] - dep[p]);
    }
};
