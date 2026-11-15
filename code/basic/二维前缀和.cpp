#include <vector>

#include "../types.hpp"

std::vector<std::vector<ll>> prefixSums2D(
    const std::vector<std::vector<int>>& a) {
    int n = static_cast<int>(a.size());
    int m = n == 0 ? 0 : static_cast<int>(a[0].size());
    std::vector<std::vector<ll>> pre(
        n + 1, std::vector<ll>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        ll rowSum = 0;
        for (int j = 1; j <= m; ++j) {
            rowSum += a[i - 1][j - 1];
            pre[i][j] = pre[i - 1][j] + rowSum;
        }
    }
    return pre;
}

ll rectangleSum(const std::vector<std::vector<ll>>& pre,
                       int x1, int y1, int x2, int y2) {
    return (pre[x2][y2] - pre[x1 - 1][y2])
         - (pre[x2][y1 - 1] - pre[x1 - 1][y1 - 1]);
}
