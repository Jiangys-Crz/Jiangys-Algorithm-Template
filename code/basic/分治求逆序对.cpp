#include <vector>

using ll = long long;

// 先准备数组 a，计算过程中将对其原地排序。

vector<int> buffer(a.size());
auto solve = [&](auto&& self, int l, int r) -> ll {
    if (r - l <= 1) {
        return 0;
    }
    int mid = l + (r - l) / 2;
    ll count = self(self, l, mid) + self(self, mid, r);
    int i = l, j = mid, k = l;
    while (i < mid && j < r) {
        if (a[i] <= a[j]) {
            buffer[k++] = a[i++];
        } else {
            count += mid - i;
            buffer[k++] = a[j++];
        }
    }
    while (i < mid) {
        buffer[k++] = a[i++];
    }
    while (j < r) {
        buffer[k++] = a[j++];
    }
    for (int p = l; p < r; ++p) {
        a[p] = buffer[p];
    }
    return count;
};
ll ans = solve(solve, 0, static_cast<int>(a.size()));
