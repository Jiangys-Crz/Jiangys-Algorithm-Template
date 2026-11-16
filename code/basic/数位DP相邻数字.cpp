using ll = long long;
using ull = unsigned long long;

// bound 为非负上界。若上界为负，方案数为 0。

const string digits = to_string(bound);
const int length = static_cast<int>(digits.size());
constexpr int noPrevious = 10;
constexpr ull unseen = numeric_limits<ull>::max();
vector<array<ull, 11>> memo(length);
for (auto& row : memo) row.fill(unseen);

auto dfs = [&](auto&& self, int pos, int previous, bool tight) -> ull {
    if (pos == length) return 1;
    if (!tight && memo[pos][previous] != unseen) return memo[pos][previous];

    const int boundDigit = digits[pos] - '0';
    const int limit = tight ? boundDigit : 9;
    ull ways = 0;
    for (int digit = 0; digit <= limit; ++digit) {
        if (previous != noPrevious) {
            // 若 digit 可接在前一个有效数位之后，条件取 true。
            bool allowed = /* 待填写：previous 与 digit 相邻的合法性 */;
            if (!allowed) continue;
        }
        const int next = previous == noPrevious && digit == 0
                             ? noPrevious : digit;
        ways += self(self, pos + 1, next, tight && digit == boundDigit);
    }
    if (!tight) memo[pos][previous] = ways;
    return ways;
};
ull ans = bound < 0 ? 0 : dfs(dfs, 0, noPrevious, true);
