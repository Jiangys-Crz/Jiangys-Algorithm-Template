#include <algorithm>

#include "tree.hpp"

std::vector<int> treeCentroids(const Tree& tr) {
    std::vector<int> res;
    for (int u = 1; u <= tr.n; ++u) {
        int largest = tr.n - tr.siz[u];
        for (int v : tr.adj[u]) {
            if (tr.fa[v] == u) largest = std::max(largest, tr.siz[v]);
        }
        if (largest <= tr.n / 2) res.push_back(u);
    }
    return res;
}
