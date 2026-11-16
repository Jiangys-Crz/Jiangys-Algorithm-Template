#include <algorithm>
#include <string_view>
#include <vector>

// In solve: pattern t and text s. z[] is for t; ext[] matches prefixes of t.
int n = static_cast<int>(s.size()), m = static_cast<int>(t.size());
std::vector<int> z(m), ext(n);
if (m) z[0] = m;
for (int i = 1, l = 0, r = 0; i < m; ++i) {
    if (i < r) z[i] = std::min(r - i, z[i - l]);
    while (z[i] < m - i && t[z[i]] == t[i + z[i]]) ++z[i];
    if (i + z[i] > r) {
        l = i;
        r = i + z[i];
    }
}

for (int i = 0, l = 0, r = 0; i < n; ++i) {
    if (i < r) ext[i] = std::min(r - i, z[i - l]);
    while (ext[i] < m && ext[i] < n - i && t[ext[i]] == s[i + ext[i]]) {
        ++ext[i];
    }
    if (i + ext[i] > r) {
        l = i;
        r = i + ext[i];
    }
}
