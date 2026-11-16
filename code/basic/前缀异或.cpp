#include <cstddef>
#include <vector>

using ull = unsigned long long;

// 先准备数组 a 和查询区间 [l, r)，下标从 0 开始。
vector<ull> p(a.size() + 1);
for (size_t i = 0; i < a.size(); ++i) p[i + 1] = p[i] ^ a[i];
ull ans = p[r] ^ p[l];
