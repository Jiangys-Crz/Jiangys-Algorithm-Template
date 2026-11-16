#ifndef XCPC_TREE_TREE_HPP
#define XCPC_TREE_TREE_HPP

struct Tree {
    int n, root = 0;
    vector<vector<int>> adj;
    vector<int> fa, dep, siz, dfn, id;

    explicit Tree(int n)
        : n(n), adj(n + 1), fa(n + 1), dep(n + 1),
          siz(n + 1), dfn(n + 1), id(n + 1) {}

    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void work(int rt = 1) {
        root = rt;
        fa[root] = dep[root] = 0;
        vector<int> stk{root};
        int cnt = 0;
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            dfn[u] = ++cnt;
            id[cnt] = u;
            siz[u] = 1;
            for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it) {
                int v = *it;
                if (v == fa[u]) continue;
                fa[v] = u;
                dep[v] = dep[u] + 1;
                stk.push_back(v);
            }
        }
        for (int i = n; i >= 2; --i) {
            int u = id[i];
            siz[fa[u]] += siz[u];
        }
    }

    pair<int, int> subtree(int u) const {
        return {dfn[u], dfn[u] + siz[u] - 1};
    }

    bool isAncestor(int u, int v) const {
        auto [l, r] = subtree(u);
        return l <= dfn[v] && dfn[v] <= r;
    }
};

#endif

#ifndef XCPC_TREE_HLD_HPP
#define XCPC_TREE_HLD_HPP

struct HLD : Tree {
    vector<int> top, son;

    explicit HLD(int n) : Tree(n), top(n + 1), son(n + 1) {}

    void work(int rt = 1) {
        Tree::work(rt);
        for (int u = 1; u <= n; ++u) {
            son[u] = 0;
            for (int v : adj[u]) {
                if (fa[v] == u && siz[v] > siz[son[u]]) son[u] = v;
            }
        }

        vector<int> stk{root};
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
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    template<class F>
    void for_path(int u, int v, F visit, bool edge = false) const {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            visit(dfn[top[u]], dfn[u]);
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        int l = dfn[u] + edge, r = dfn[v];
        if (l <= r) visit(l, r);
    }
};

#endif
