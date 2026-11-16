#include <vector>

using ll = long long;
using lll = __int128;

// a 为非递减数组，target 为目标和。

int l = 0, r = static_cast<int>(a.size()) - 1;
while (l < r) {
    lll sum = lll(a[l]) + a[r];
    if (sum == target) break;
    if (sum < target) ++l;
    else --r;
}
// 若 l < r，则 (l, r) 为一组解，否则无解。
