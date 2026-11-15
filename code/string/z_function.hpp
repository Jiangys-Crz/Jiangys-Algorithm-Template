#include <algorithm>
#include <string_view>
#include <vector>

#ifndef XCPC_STRING_Z_FUNCTION_HPP
#define XCPC_STRING_Z_FUNCTION_HPP

inline std::vector<int> zFunction(std::string_view s) {
    int n = static_cast<int>(s.size());
    std::vector<int> z(n);
    if (!n) return z;
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i < r) z[i] = std::min(r - i, z[i - l]);
        while (z[i] < n - i && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

inline std::vector<int> extendedLcp(std::string_view s, std::string_view t) {
    int n = static_cast<int>(s.size()), m = static_cast<int>(t.size());
    auto z = zFunction(t);
    std::vector<int> ext(n);
    for (int i = 0, l = 0, r = 0; i < n; ++i) {
        if (i < r) ext[i] = std::min(r - i, z[i - l]);
        while (ext[i] < m && ext[i] < n - i &&
               t[ext[i]] == s[i + ext[i]]) ++ext[i];
        if (i + ext[i] > r) {
            l = i;
            r = i + ext[i];
        }
    }
    return ext;
}

#endif
