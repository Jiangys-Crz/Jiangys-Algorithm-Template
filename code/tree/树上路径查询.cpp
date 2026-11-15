#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

using ll = long long;

#ifndef XCPC_DS_FENWICK_HPP
#define XCPC_DS_FENWICK_HPP

template<class T>
struct Fenwick {
    int n;
    std::vector<T> f;

    explicit Fenwick(int n) : n(n), f(n + 1) {}

    void add(int x, T val) {
        assert(1 <= x && x <= n);
        for (std::size_t i = x; i < f.size(); i += i & -i) f[i] += val;
    }

    T query(int x) const {
        T res{};
        for (int i = x; i; i -= i & -i) res += f[i];
        return res;
    }

    T rangesum(int l, int r) const {
        return l > r ? T{} : query(r) - query(l - 1);
    }

    int kth(T k) const {
        if (k <= T{} || k > query(n)) return 0;
        int step = 1, x = 0;
        while (step <= n / 2) step *= 2;
        for (; step; step /= 2) {
            if (step > n - x || f[x + step] >= k) continue;
            x += step;
            k -= f[x];
        }
        return x + 1;
    }
};

#endif

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

#ifndef XCPC_TREE_HLD_HPP
#define XCPC_TREE_HLD_HPP

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

#endif

class RangeFenwick {
public:
    explicit RangeFenwick(int n) : b1(n), b2(n) {}

    void modify(int l, int r, ll val) {
        b1.add(l, val);
        b2.add(l, val * (l - 1));
        if (r < b1.n) {
            b1.add(r + 1, -val);
            b2.add(r + 1, -val * r);
        }
    }

    ll query(int l, int r) const {
        return prefix(r) - prefix(l - 1);
    }

private:
    Fenwick<ll> b1, b2;

    ll prefix(int i) const {
        return i * b1.query(i) - b2.query(i);
    }
};

struct TreePathSum {
    const HLD& tr;
    RangeFenwick bit;

    TreePathSum(const HLD& tr, const std::vector<ll>& a)
        : tr(tr), bit(tr.n) {
        for (int u = 1; u <= tr.n; ++u) {
            bit.modify(tr.dfn[u], tr.dfn[u], a[u]);
        }
    }

    void modify_path(int u, int v, ll val) {
        tr.for_path(u, v, [&](int l, int r) { bit.modify(l, r, val); });
    }

    ll query_path(int u, int v) const {
        ll res = 0;
        tr.for_path(u, v, [&](int l, int r) { res += bit.query(l, r); });
        return res;
    }

    void modify_tree(int u, ll val) {
        auto [l, r] = tr.subtree(u);
        bit.modify(l, r, val);
    }

    ll query_tree(int u) const {
        auto [l, r] = tr.subtree(u);
        return bit.query(l, r);
    }
};
