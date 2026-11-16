#include <algorithm>
#include <cstddef>
#include <string>

// 先准备字符串 s。pos 为字典序最小的轮转中最靠前的起点。

auto n = s.size();
size_t i = 0, j = 1, k = 0;
while (i < n && j < n && k < n) {
    unsigned char a = s[(i + k) % n], b = s[(j + k) % n];
    if (a == b) {
        ++k;
    } else {
        if (a > b) i += k + 1;
        else j += k + 1;
        if (i == j) ++j;
        k = 0;
    }
}
auto pos = min(i, j);
