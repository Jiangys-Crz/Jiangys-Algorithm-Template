#include <cstddef>
#include <string>
#include <string_view>

// 先将待枚举的字符串表示为视图 s。
for (size_t l = 0; l < s.size(); ++l) {
    for (size_t r = l + 1; r <= s.size(); ++r) {
        auto part = s.substr(l, r - l);
        // 待填写：处理区间 [l, r) 对应的子串 part。
    }
}

string chosen;
chosen.reserve(s.size());
auto dfs = [&](auto&& self, size_t i) -> void {
    if (i == s.size()) {
        // 待填写：处理当前子序列 chosen，包含空序列。
        return;
    }
    self(self, i + 1);
    chosen.push_back(s[i]);
    self(self, i + 1);
    chosen.pop_back();
};
dfs(dfs, 0);
