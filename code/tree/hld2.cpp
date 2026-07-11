template<class T>
struct HLD {
    int n;
    std::vector<std::vector<int>> adj; // 图
    std::vector<int> siz, dep; // 大小、节点深度
    std::vector<int> fa; // 父节点数组
    std::vector<std::array<int, 17>> f; //倍增数组
    std::vector<i64> dp; //换根dp数组，当前点到其他每个点的距离和
    std::vector<T> w; // 点权数组

    HLD(int n_) {
        n = n_;
        adj.resize(n + 1);
        siz.resize(n + 1);
        dep.resize(n + 1);
        fa.resize(n + 1);
        f.resize(n + 1);
        dp.resize(n + 1);
    }
    
    HLD(std::vector<T> &w): HLD(int(w.size())) {
        init(w);
    }

    void init(std::vector<T> &w) {
        this->w = w;
    }

    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::function<void(int)> dfs1 = [&](int cur) -> void {
        dp[1] += dep[fa[cur]];
        dep[cur] = dep[fa[cur]] + 1;
        siz[cur] = 1;
        f[cur][0] = fa[cur];
        for (int j = 1; j <= 16; j++) {
            f[cur][j] = f[f[cur][j - 1]][j - 1];
        }
        for (auto v : adj[cur]) {
            if (v == fa[cur]) {
                continue;
            }
            fa[v] = cur;
            dfs1(v);
            siz[cur] += siz[v];
        }
    };
    std::function<void(int)> dfs2 = [&](int cur) -> void {
        for (auto v : adj[cur]) {
            if (v == fa[cur]) {
                continue;
            }
            dp[v] = dp[cur] + n - 2 * siz[v];
            dfs2(v);
        }
    };

    std::function<int(int, int)> lca = [&](int x, int y) -> int {
        if (dep[x] < dep[y]) {
            std::swap(x, y);
        }
        for (int j = 16; j >= 0; j--) {
            if (dep[f[x][j]] >= dep[y]) {
                x = f[x][j];
            }
        }
        if (x == y) {
            return x;
        }
        for (int j = 16; j >= 0; j--) {
            if (f[x][j] != f[y][j]) {
                x = f[x][j];
                y = f[y][j];
            }
        }
        return f[x][0];
    };

    // 查询两点间的距离
    int calc(int x, int y) {
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }

    // 查询两点的点权值和
    T getSum(int x, int y) {
        int t = lca(x, y);
        return w[x] + w[y] - w[t] - w[fa[t]];
    }

    void work(int root = 1) {
        dfs1(root);
        dfs2(root);
    }
};