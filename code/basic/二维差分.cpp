#include <vector>

using ll = long long;

// In solve: 1-based n by m matrix a and updates (x1, y1, x2, y2, delta).

std::vector<std::vector<ll>> d(n + 2, std::vector<ll>(m + 2));
auto add = [&](int x1, int y1, int x2, int y2, ll v) {
    d[x1][y1] += v;
    d[x2 + 1][y1] -= v;
    d[x1][y2 + 1] -= v;
    d[x2 + 1][y2 + 1] += v;
};

for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
        add(i, j, i, j, a[i][j]);
    }
}
for (auto [x1, y1, x2, y2, v] : updates) {
    add(x1, y1, x2, y2, v);
}

for (int i = 1; i <= n; ++i) {
    ll row = 0;
    for (int j = 1; j <= m; ++j) {
        row += d[i][j];
        d[i][j] = d[i - 1][j] + row;
    }
}
// d[1..n][1..m] now contains the updated matrix.
