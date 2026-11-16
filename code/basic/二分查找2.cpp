#include <vector>

using ll = long long;

// 先准备长度为 n 的非递减数组 a 和待查值 x，下标从 1 开始。
// ans 为边界下标。哨兵 0 或 n + 1 表示无符合条件的位置。

int l = 0, r = n;
while (l < r) {
    int mid = r - (r - l) / 2;
    if (a[mid] <= x) l = mid;
    else r = mid - 1;
}
int ans = l;
