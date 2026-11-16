#include <array>
#include <vector>

using ll = long long;

// In solve: tr is a preprocessed Tree. Adapt the DP states to the problem.
std::vector<std::array<ll, 2>> dp(tr.n + 1);
for (int u = 1; u <= tr.n; ++u) {
    dp[u] = /* TODO: initial states of u before merging its children */;
}

for (int i = tr.n; i >= 2; --i) {
    int u = tr.id[i], p = tr.fa[u];
    // TODO: Merge the completed states of child u into parent p.
}
ll ans = /* TODO: extract the answer from dp[tr.root] */;
