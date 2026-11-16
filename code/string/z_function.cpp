#include <algorithm>
#include <string_view>
#include <vector>

// 先准备模式串 t 和文本 s。z 为 t 的 Z 函数，ext 为各位置与 t 的最长公共前缀长度。
int n = static_cast<int>(s.size()), m = static_cast<int>(t.size());
vector<int> z(m), ext(n);
if (m) z[0] = m;
for (int i = 1, l = 0, r = 0; i < m; ++i) {
    if (i < r) z[i] = min(r - i, z[i - l]);
    while (z[i] < m - i && t[z[i]] == t[i + z[i]]) ++z[i];
    if (i + z[i] > r) {
        l = i;
        r = i + z[i];
    }
}

for (int i = 0, l = 0, r = 0; i < n; ++i) {
    if (i < r) ext[i] = min(r - i, z[i - l]);
    while (ext[i] < m && ext[i] < n - i && t[ext[i]] == s[i + ext[i]]) {
        ++ext[i];
    }
    if (i + ext[i] > r) {
        l = i;
        r = i + ext[i];
    }
}
