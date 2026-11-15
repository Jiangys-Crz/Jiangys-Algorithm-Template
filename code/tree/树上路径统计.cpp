#include "../types.hpp"
#include "tree.hpp"

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
