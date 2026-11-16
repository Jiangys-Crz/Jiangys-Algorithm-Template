#include <iostream>
#include <vector>

using ll = long long;

int main() {
    int n, m, q;
    if (!(std::cin >> n >> m >> q)) return 0;
    std::vector<std::vector<ll>> d(n + 2, std::vector<ll>(m + 2));
    auto add = [&](int x1, int y1, int x2, int y2, ll v) {
        d[x1][y1] += v;
        d[x2 + 1][y1] -= v;
        d[x1][y2 + 1] -= v;
        d[x2 + 1][y2 + 1] += v;
    };

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            ll x;
            std::cin >> x;
            add(i, j, i, j, x);
        }
    }
    while (q--) {
        int x1, y1, x2, y2;
        ll v;
        std::cin >> x1 >> y1 >> x2 >> y2 >> v;
        add(x1, y1, x2, y2, v);
    }

    for (int i = 1; i <= n; ++i) {
        ll row = 0;
        for (int j = 1; j <= m; ++j) {
            row += d[i][j];
            d[i][j] = d[i - 1][j] + row;
            std::cout << d[i][j] << (j == m ? '\n' : ' ');
        }
    }
}
