#include <utility>
#include <vector>

using ll = long long;

#ifndef XCPC_TREE_TREE_HPP
#define XCPC_TREE_TREE_HPP

struct Tree {
    int n, root = 0;
    std::vector<std::vector<int>> adj;
    std::vector<int> fa, dep, siz, dfn, id;

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
        std::vector<int> stk{root};
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

    std::pair<int, int> subtree(int u) const {
        return {dfn[u], dfn[u] + siz[u] - 1};
    }

    bool isAncestor(int u, int v) const {
        auto [l, r] = subtree(u);
        return l <= dfn[v] && dfn[v] <= r;
    }
};

#endif

#ifndef XCPC_TREE_PATH_PREFIX_HPP
#define XCPC_TREE_PATH_PREFIX_HPP

struct TreePrefix {
    std::vector<int> fa;
    std::vector<ll> pre;

    TreePrefix(const Tree& tr, const std::vector<ll>& a)
        : fa(tr.fa), pre(tr.n + 1) {
        for (int i = 1; i <= tr.n; ++i) {
            int u = tr.id[i];
            pre[u] = pre[fa[u]] + a[u];
        }
    }

    ll nodeSum(int u, int v, int p) const {
        return (pre[u] - pre[p]) + (pre[v] - pre[fa[p]]);
    }

    ll edgeSum(int u, int v, int p) const {
        return (pre[u] - pre[p]) + (pre[v] - pre[p]);
    }
};

#endif
