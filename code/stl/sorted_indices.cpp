#include <algorithm>
#include <numeric>
#include <vector>

using ll = long long;

// 先准备数组 a。id 按数值从小到大保存原下标。

vector<int> id(a.size());
iota(id.begin(), id.end(), 0);
sort(id.begin(), id.end(), [&](int i, int j) {
    if (a[i] != a[j]) return a[i] < a[j];
    return i < j;
});
