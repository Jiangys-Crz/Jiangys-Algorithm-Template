#include "tree.hpp"

std::vector<int> minVertexCover(const Tree& tr) {
    std::vector<char> chosen(tr.n + 1);
    std::vector<int> cover;

    for (int i = tr.n; i >= 2; --i) {
        int u = tr.id[i], p = tr.fa[u];
        if (!chosen[u] && !chosen[p]) {
            chosen[p] = true;
            cover.push_back(p);
        }
    }
    return cover;
}
