#include <numeric>
#include <string_view>
#include <vector>

// 先准备文本 s 和模式串 t。ans 保存从 0 开始的匹配起点。
int n = static_cast<int>(s.size()), m = static_cast<int>(t.size());
vector<int> nxt(m), ans;
for (int i = 1, j = 0; i < m; ++i) {
    while (j && t[i] != t[j]) j = nxt[j - 1];
    if (t[i] == t[j]) ++j;
    nxt[i] = j;
}

if (m == 0) {
    ans.resize(s.size() + 1);
    iota(ans.begin(), ans.end(), 0LL);
} else {
    for (int i = 0, j = 0; i < n; ++i) {
        while (j && s[i] != t[j]) j = nxt[j - 1];
        if (s[i] == t[j]) ++j;
        if (j == m) {
            ans.push_back(i - m + 1);
            j = nxt[j - 1];
        }
    }
}
