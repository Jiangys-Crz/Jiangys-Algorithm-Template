#include <cstddef>
#include <vector>

using ll = long long;

// 先准备位数 n 和长度为 2^n 的权值数组 values。
// 计算后，values[mask] 为 mask 的所有子掩码的权值和。

for (int bit = 0; bit < n; ++bit) {
    const size_t flag = size_t{1} << bit;
    for (size_t mask = 0; mask < values.size(); ++mask) {
        if ((mask & flag) != 0) {
            values[mask] += values[mask ^ flag];
        }
    }
}
