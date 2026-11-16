#include <algorithm>
#include <vector>

using ll = long long;

// a 为非递减数组，x 为待查值。

auto l = lower_bound(a.begin(), a.end(), x);
auto r = upper_bound(l, a.end(), x);
auto first = l - a.begin(), last = r - a.begin();
