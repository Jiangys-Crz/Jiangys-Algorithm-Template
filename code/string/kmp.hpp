#include <numeric>
#include <string>
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

#ifndef XCPC_STRING_KMP_HPP
#define XCPC_STRING_KMP_HPP

struct KMP {
    std::string t;
    std::vector<int> nxt;

    explicit KMP(std::string_view pattern) : t(pattern), nxt(prefixFunction(t)) {}

    std::vector<int> query(std::string_view s) const {
        int n = static_cast<int>(s.size()), m = static_cast<int>(t.size());
        if (!m) {
            std::vector<int> ans(s.size() + 1);
            std::iota(ans.begin(), ans.end(), 0);
            return ans;
        }
        std::vector<int> ans;
        for (int i = 0, j = 0; i < n; ++i) {
            while (j && s[i] != t[j]) j = nxt[j - 1];
            if (s[i] == t[j]) ++j;
            if (j == m) {
                ans.push_back(i - m + 1);
                j = nxt[j - 1];
            }
        }
        return ans;
    }
};

#endif
