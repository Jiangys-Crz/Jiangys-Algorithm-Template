#ifndef XCPC_DS_DSU_HPP
#define XCPC_DS_DSU_HPP

struct DSU {
    vector<int> fa, siz, rk;

    explicit DSU(int n)
        : fa(n + 1), siz(n + 1, 1), rk(n + 1) {
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int u) {
        while (u != fa[u]) u = fa[u] = fa[fa[u]];
        return u;
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (rk[u] < rk[v]) swap(u, v);
        fa[v] = u;
        siz[u] += siz[v];
        if (rk[u] == rk[v]) ++rk[u];
        return true;
    }

    int size(int u) {
        return siz[find(u)];
    }
};

#endif

struct ParityConstraints {
    int n;
    DSU dsu;

    explicit ParityConstraints(int n) : n(n), dsu(2 * n) {}

    bool add(int u, int v, bool different) {
        if (different) {
            if (dsu.same(u, v)) return false;
            dsu.merge(u, v + n);
            dsu.merge(u + n, v);
        } else {
            if (dsu.same(u, v + n)) return false;
            dsu.merge(u, v);
            dsu.merge(u + n, v + n);
        }
        return true;
    }

    optional<bool> relation(int u, int v) {
        if (dsu.same(u, v)) return false;
        if (dsu.same(u, v + n)) return true;
        return nullopt;
    }
};
