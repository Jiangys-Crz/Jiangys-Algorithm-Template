#include <vector>

void addRectangle(std::vector<std::vector<long long>>& diff,
                  int x1, int y1, int x2, int y2, long long delta) {
    diff[x1][y1] += delta;
    diff[x2 + 1][y1] -= delta;
    diff[x1][y2 + 1] -= delta;
    diff[x2 + 1][y2 + 1] += delta;
}

std::vector<std::vector<long long>> buildDifference2D(
    const std::vector<std::vector<int>>& a) {
    int n = static_cast<int>(a.size());
    int m = n == 0 ? 0 : static_cast<int>(a[0].size());
    std::vector<std::vector<long long>> diff(
        n + 2, std::vector<long long>(m + 2, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            addRectangle(diff, i, j, i, j, a[i - 1][j - 1]);
        }
    }
    return diff;
}

std::vector<std::vector<long long>> restoreMatrix(
    const std::vector<std::vector<long long>>& diff) {
    int n = static_cast<int>(diff.size()) - 2;
    int m = static_cast<int>(diff[0].size()) - 2;
    std::vector<std::vector<long long>> a(n, std::vector<long long>(m));
    for (int i = 1; i <= n; ++i) {
        long long rowSum = 0;
        for (int j = 1; j <= m; ++j) {
            rowSum += diff[i][j];
            a[i - 1][j - 1] = rowSum;
            if (i > 1) {
                a[i - 1][j - 1] += a[i - 2][j - 1];
            }
        }
    }
    return a;
}
