struct RollbackDSU {
    struct Change {
        int u, v, oldSize;
    };

    int cnt;
    vector<int> fa, siz;
    vector<Change> stk;

    explicit RollbackDSU(int n) : cnt(n), fa(n + 1), siz(n + 1, 1) {
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int u) const {
        while (u != fa[u]) u = fa[u];
        return u;
    }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (siz[u] < siz[v]) swap(u, v);
        stk.push_back({u, v, siz[u]});
        fa[v] = u;
        siz[u] += siz[v];
        --cnt;
        return true;
    }

    size_t snapshot() const {
        return stk.size();
    }

    void rollback(size_t time) {
        while (stk.size() > time) {
            auto [u, v, oldSize] = stk.back();
            stk.pop_back();
            fa[v] = v;
            siz[u] = oldSize;
            ++cnt;
        }
    }
};
