#include <algorithm>
#include <vector>

using ll = long long;

// 先准备数组 a，要求 1 <= k <= a.size()。
// 该操作可能改变 a 中元素的顺序。

auto it = a.begin() + (k - 1);
nth_element(a.begin(), it, a.end());
ll ans = *it;
