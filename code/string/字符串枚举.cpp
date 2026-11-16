#include <cstddef>
#include <string>
#include <string_view>

// In solve: string_view s (or a view of the original string).
for (std::size_t l = 0; l < s.size(); ++l) {
    for (std::size_t r = l + 1; r <= s.size(); ++r) {
        auto part = s.substr(l, r - l);
        // TODO: Process substring part at [l, r).
    }
}

std::string chosen;
chosen.reserve(s.size());
auto dfs = [&](auto&& self, std::size_t i) -> void {
    if (i == s.size()) {
        // TODO: Process the current subsequence chosen, including empty.
        return;
    }
    self(self, i + 1);
    chosen.push_back(s[i]);
    self(self, i + 1);
    chosen.pop_back();
};
dfs(dfs, 0);
