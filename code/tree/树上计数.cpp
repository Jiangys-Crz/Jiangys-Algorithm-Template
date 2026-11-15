#include <array>

#include "../types.hpp"
#include "tree.hpp"

int countIndependentSets(const Tree& tr) {
    constexpr ll mod = 1000000007;
    std::vector<std::array<ll, 2>> dp(tr.n + 1, {1, 1});
    for (int i = tr.n; i >= 2; --i) {
        int u = tr.id[i], p = tr.fa[u];
        dp[p][0] = dp[p][0] * ((dp[u][0] + dp[u][1]) % mod) % mod;
        dp[p][1] = dp[p][1] * dp[u][0] % mod;
    }
    return (dp[tr.root][0] + dp[tr.root][1]) % mod;
}
