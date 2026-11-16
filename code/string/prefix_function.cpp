#include <string>
#include <vector>

// In solve: string or string_view s. nxt[i] is the prefix-function value.

int n = static_cast<int>(s.size());
std::vector<int> nxt(n);
for (int i = 1, j = 0; i < n; ++i) {
    while (j && s[i] != s[j]) j = nxt[j - 1];
    if (s[i] == s[j]) ++j;
    nxt[i] = j;
}
