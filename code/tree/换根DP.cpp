#include "../types.hpp"
#include "tree.hpp"

std::vector<ll> sumDistances(const Tree& tr) {
    std::vector<ll> dp(tr.n + 1);
    for (int u = 1; u <= tr.n; ++u) dp[tr.root] += tr.dep[u];

    for (int i = 2; i <= tr.n; ++i) {
        int u = tr.id[i];
        dp[u] = dp[tr.fa[u]] + tr.n - 2LL * tr.siz[u];
    }
    return dp;
}
