#include <algorithm>
#include <limits>
#include <optional>
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

std::optional<ll> treeKnapsack(const Tree& tr,
                                      const std::vector<ll>& a, int k) {
    if (k < 1 || k > tr.n) return std::nullopt;
    std::vector<std::vector<ll>> dp(tr.n + 1);
    for (int i = tr.n; i >= 1; --i) {
        int u = tr.id[i];
        dp[u] = {0, a[u]};
        for (int v : tr.adj[u]) {
            if (tr.fa[v] != u) continue;
            int have = static_cast<int>(dp[u].size()) - 1;
            int take = static_cast<int>(dp[v].size()) - 1;
            int cap = have + std::min(take, k - have);
            std::vector<ll> next(cap + 1,
                                        std::numeric_limits<ll>::lowest());
            next[0] = 0;
            for (int x = 1; x <= have; ++x) {
                for (int y = 0; y <= std::min(take, cap - x); ++y) {
                    next[x + y] = std::max(next[x + y], dp[u][x] + dp[v][y]);
                }
            }
            dp[u].swap(next);
        }
    }
    return dp[tr.root][k];
}
