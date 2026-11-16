#include <vector>

using ll = long long;

// In solve: n by m matrix a with 1-based coordinates.
// Query corners: (x1, y1), (x2, y2), inclusive.
std::vector<std::vector<ll>> pre(n + 1, std::vector<ll>(m + 1));
for (int i = 1; i <= n; ++i) {
    ll row = 0;
    for (int j = 1; j <= m; ++j) {
        row += a[i][j];
        pre[i][j] = pre[i - 1][j] + row;
    }
}

ll ans = (pre[x2][y2] - pre[x1 - 1][y2])
       - (pre[x2][y1 - 1] - pre[x1 - 1][y1 - 1]);
