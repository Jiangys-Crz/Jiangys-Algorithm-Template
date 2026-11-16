#include <algorithm>
#include <limits>
#include <string>
#include <vector>

// 先准备字符串数组 a。排序后依次拼接，得到字典序最小的结果。

sort(a.begin(), a.end(), [](const string& x, const string& y) {
    if (x.empty() != y.empty()) return x.empty();
    for (size_t i = 0; i < x.size() + y.size(); ++i) {
        unsigned char u = i < x.size() ? x[i] : y[i - x.size()];
        unsigned char v = i < y.size() ? y[i] : x[i - y.size()];
        if (u != v) return u < v;
    }
    return false;
});
