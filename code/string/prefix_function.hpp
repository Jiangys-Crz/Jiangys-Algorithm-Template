#pragma once

#include <string_view>
#include <vector>

inline std::vector<int> prefixFunction(std::string_view s) {
    int n = static_cast<int>(s.size());
    std::vector<int> nxt(n);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j && s[i] != s[j]) j = nxt[j - 1];
        if (s[i] == s[j]) ++j;
        nxt[i] = j;
    }
    return nxt;
}
