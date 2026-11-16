#include <numeric>
#include <utility>
#include <vector>

#ifndef XCPC_GRAPH_GRAPH_DSU_HPP
#define XCPC_GRAPH_GRAPH_DSU_HPP

struct GraphDSU {
    vector<int> fa, siz;

    explicit GraphDSU(int n) : fa(n + 1), siz(n + 1, 1) {
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int u) {
        while (u != fa[u]) {
            fa[u] = fa[fa[u]];
            u = fa[u];
        }
        return u;
    }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (siz[u] < siz[v]) swap(u, v);
        fa[v] = u;
        siz[u] += siz[v];
        return true;
    }
};

#endif
