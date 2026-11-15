#include <string_view>
#include <vector>

#ifndef XCPC_STRING_PREFIX_FUNCTION_HPP
#define XCPC_STRING_PREFIX_FUNCTION_HPP

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

#endif

struct StringPeriod {
    int step, block;
};

StringPeriod stringPeriod(std::string_view s) {
    if (s.empty()) return {0, 0};
    int n = static_cast<int>(s.size());
    int p = n - prefixFunction(s).back();
    return {p, n % p == 0 ? p : n};
}
