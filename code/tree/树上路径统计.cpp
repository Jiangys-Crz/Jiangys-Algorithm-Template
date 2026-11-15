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

ll countPairsAtDistance(const Tree& tr, int k) {
    if (k <= 0 || k >= tr.n) return 0;
    std::vector<std::vector<int>> dp(tr.n + 1, std::vector<int>(k + 1));

    ll ans = 0;
    for (int i = tr.n; i >= 1; --i) {
        int u = tr.id[i];
        dp[u][0] = 1;
        for (int v : tr.adj[u]) {
            if (tr.fa[v] != u) continue;
            for (int d = 0; d < k; ++d) {
                ans += 1LL * dp[u][k - 1 - d] * dp[v][d];
            }
            for (int d = 0; d < k; ++d) dp[u][d + 1] += dp[v][d];
        }
    }
    return ans;
}
