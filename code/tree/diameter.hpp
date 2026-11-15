#pragma once

#include <algorithm>

#include "tree_bfs.hpp"

struct Diameter {
    int u, v, len;
    std::vector<int> path;
};

inline Diameter treeDiameter(const Tree& tr) {
    int u = TreeBfs(tr).order.back();
    TreeBfs bfs(tr, u);
    int v = bfs.order.back();

    std::vector<int> path;
    for (int x = v; x; x = bfs.fa[x]) path.push_back(x);
    std::reverse(path.begin(), path.end());
    return {u, v, bfs.dep[v], std::move(path)};
}
