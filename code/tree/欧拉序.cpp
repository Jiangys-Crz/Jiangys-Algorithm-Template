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

struct EulerTour {
    vector<int> id, first;

    explicit EulerTour(const Tree& tr) : first(tr.n + 1) {
        vector<int> stk{tr.root};
        id.push_back(tr.root);
        for (int i = 2; i <= tr.n; ++i) {
            int u = tr.id[i];
            while (stk.back() != tr.fa[u]) {
                stk.pop_back();
                id.push_back(stk.back());
            }
            first[u] = static_cast<int>(id.size());
            id.push_back(u);
            stk.push_back(u);
        }
        while (stk.size() > 1) {
            stk.pop_back();
            id.push_back(stk.back());
        }
    }
};
