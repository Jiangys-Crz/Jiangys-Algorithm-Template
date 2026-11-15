#pragma once

#include "tree.hpp"

struct TreeBfs {
    std::vector<int> order, fa, dep;

    explicit TreeBfs(const Tree& tr, int root = 1)
        : fa(tr.n + 1), dep(tr.n + 1) {
        order.push_back(root);
        for (int i = 0; i < static_cast<int>(order.size()); ++i) {
            int u = order[i];
            for (int v : tr.adj[u]) {
                if (v == fa[u]) continue;
                fa[v] = u;
                dep[v] = dep[u] + 1;
                order.push_back(v);
            }
        }
    }
};
