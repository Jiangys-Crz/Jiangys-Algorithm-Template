#include <algorithm>
#include <limits>

#include "../types.hpp"
#include "tree.hpp"

ll weightedDiameter(const Tree& tr, const std::vector<ll>& w) {
    if (tr.n == 1) return 0;

    std::vector<ll> down(tr.n + 1);
    ll ans = std::numeric_limits<ll>::lowest();
    for (int i = tr.n; i >= 2; --i) {
        int u = tr.id[i], p = tr.fa[u];
        ll branch = down[u] + w[u];
        ans = std::max(ans, down[p] + branch);
        down[p] = std::max(down[p], branch);
    }
    return ans;
}
