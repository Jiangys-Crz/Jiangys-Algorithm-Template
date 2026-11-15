#pragma once

#include "tree.hpp"

struct HLD : Tree {
    std::vector<int> top, son;

    explicit HLD(int n) : Tree(n), top(n + 1), son(n + 1) {}

    void work(int rt = 1) {
        Tree::work(rt);
        for (int u = 1; u <= n; ++u) {
            son[u] = 0;
            for (int v : adj[u]) {
                if (fa[v] == u && siz[v] > siz[son[u]]) son[u] = v;
            }
        }

        std::vector<int> stk{root};
        int cnt = 0;
        while (!stk.empty()) {
            int t = stk.back();
            stk.pop_back();
            for (int u = t; u; u = son[u]) {
                top[u] = t;
                dfn[u] = ++cnt;
                id[cnt] = u;
                for (int v : adj[u]) {
                    if (fa[v] == u && v != son[u]) stk.push_back(v);
                }
            }
        }
    }

    int lca(int u, int v) const {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    template<class F>
    void for_path(int u, int v, F visit, bool edge = false) const {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
            visit(dfn[top[u]], dfn[u]);
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) std::swap(u, v);
        int l = dfn[u] + edge, r = dfn[v];
        if (l <= r) visit(l, r);
    }
};
