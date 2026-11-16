#include <numeric>
#include <string_view>
#include <vector>

// In solve: text s and pattern t. ans contains 0-based match positions.
int n = static_cast<int>(s.size()), m = static_cast<int>(t.size());
std::vector<int> nxt(m), ans;
for (int i = 1, j = 0; i < m; ++i) {
    while (j && t[i] != t[j]) j = nxt[j - 1];
    if (t[i] == t[j]) ++j;
    nxt[i] = j;
}

if (m == 0) {
    ans.resize(s.size() + 1);
    std::iota(ans.begin(), ans.end(), 0LL);
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
