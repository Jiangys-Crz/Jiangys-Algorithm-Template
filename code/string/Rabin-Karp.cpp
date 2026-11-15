#include "double_hash.hpp"

std::vector<int> rabinKarp(std::string_view s, std::string_view t) {
    std::vector<int> ans;
    auto m = t.size();
    if (m > s.size()) return ans;

    DoubleHash hs(s), ht(t);
    auto target = ht.get();
    for (std::size_t l = 0; l <= s.size() - m; ++l) {
        if (hs.substring(l, l + m) == target && s.substr(l, m) == t) {
            ans.push_back(static_cast<int>(l));
        }
    }
    return ans;
}
