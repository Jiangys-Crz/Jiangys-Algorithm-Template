#include <algorithm>
#include <limits>
#include <optional>

#include "../types.hpp"
#include "tree.hpp"

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
