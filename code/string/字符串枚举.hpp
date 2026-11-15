#pragma once

#include <cstddef>
#include <string>
#include <string_view>

template<class F>
void forEachSubstring(std::string_view s, F visit) {
    for (std::size_t l = 0; l < s.size(); ++l) {
        for (std::size_t r = l + 1; r <= s.size(); ++r) {
            visit(l, r, s.substr(l, r - l));
        }
    }
}

template<class F>
void forEachSubsequence(std::string_view s, F visit) {
    std::string chosen;
    chosen.reserve(s.size());
    auto dfs = [&](auto&& self, std::size_t i) -> void {
        if (i == s.size()) {
            visit(std::string_view(chosen));
            return;
        }
        self(self, i + 1);
        chosen.push_back(s[i]);
        self(self, i + 1);
        chosen.pop_back();
    };
    dfs(dfs, 0);
}
