#include <algorithm>
#include <vector>

using ll = long long;

// vals 保存全部待离散化的数值，x 为待查值。
sort(vals.begin(), vals.end());
vals.erase(unique(vals.begin(), vals.end()), vals.end());

auto it = lower_bound(vals.begin(), vals.end(), x);
auto rank = it != vals.end() && *it == x ? it - vals.begin() + 1 : 0;
