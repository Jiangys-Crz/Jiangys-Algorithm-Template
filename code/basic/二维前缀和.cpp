#include <iostream>
#include <vector>

using ll = long long;

int main() {
    int n, m, q;
    if (!(std::cin >> n >> m >> q)) return 0;
    std::vector<std::vector<ll>> pre(n + 1, std::vector<ll>(m + 1));
    for (int i = 1; i <= n; ++i) {
        ll row = 0;
        for (int j = 1; j <= m; ++j) {
            ll x;
            std::cin >> x;
            row += x;
            pre[i][j] = pre[i - 1][j] + row;
        }
    }

    while (q--) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        ll ans = (pre[x2][y2] - pre[x1 - 1][y2])
               - (pre[x2][y1 - 1] - pre[x1 - 1][y1 - 1]);
        std::cout << ans << '\n';
    }
}
