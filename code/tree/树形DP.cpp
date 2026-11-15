#include <algorithm>
#include <array>

#include "../types.hpp"
#include "tree.hpp"

ll maxIndependentSet(const Tree& tr, const std::vector<ll>& a) {
    std::vector<std::array<ll, 2>> dp(tr.n + 1);
    for (int u = 1; u <= tr.n; ++u) dp[u][1] = a[u];

    for (int i = tr.n; i >= 2; --i) {
        int u = tr.id[i], p = tr.fa[u];
        dp[p][0] += std::max(dp[u][0], dp[u][1]);
        dp[p][1] += dp[u][0];
    }
    return std::max(dp[tr.root][0], dp[tr.root][1]);
}
