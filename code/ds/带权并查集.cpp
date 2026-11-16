using ll = long long;

template<class T = ll>
struct WeightedDSU {
    vector<int> fa, siz;
    vector<T> dis;

    explicit WeightedDSU(int n) : fa(n + 1), siz(n + 1, 1), dis(n + 1) {
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int u) {
        if (fa[u] == u) return u;
        int p = fa[u];
        fa[u] = find(p);
        dis[u] += dis[p];
        return fa[u];
    }

    // 添加约束 value[u] - value[v] = w。
    bool merge(int u, int v, T w) {
        int x = find(u), y = find(v);
        T delta = w - dis[u] + dis[v];
        if (x == y) return delta == T{};
        if (siz[x] > siz[y]) {
            swap(x, y);
            delta = -delta;
        }
        fa[x] = y;
        dis[x] = delta;
        siz[y] += siz[x];
        return true;
    }

    optional<T> difference(int u, int v) {
        if (find(u) != find(v)) return nullopt;
        return dis[u] - dis[v];
    }
};
