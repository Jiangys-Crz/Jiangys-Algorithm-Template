#include <vector>

using ll = long long;

// a 为 n 行 m 列的矩阵，行列下标从 1 开始。
// 查询包含左上角 (x1, y1) 和右下角 (x2, y2) 的闭矩形。
vector<vector<ll>> pre(n + 1, vector<ll>(m + 1));
for (int i = 1; i <= n; ++i) {
    ll row = 0;
    for (int j = 1; j <= m; ++j) {
        row += a[i][j];
        pre[i][j] = pre[i - 1][j] + row;
    }
}

ll ans = (pre[x2][y2] - pre[x1 - 1][y2])
       - (pre[x2][y1 - 1] - pre[x1 - 1][y1 - 1]);
