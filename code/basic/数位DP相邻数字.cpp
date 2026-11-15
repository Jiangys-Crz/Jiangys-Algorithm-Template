#include <array>
#include <string>
#include <vector>

using ll = long long;

ll countWithoutEqualNeighbors(ll bound) {
    if (bound < 0) return 0;
    const std::string digits = std::to_string(bound);
    const int length = static_cast<int>(digits.size());
    constexpr int noPrevious = 10;
    std::vector<std::array<ll, 11>> memo(length);
    for (auto& row : memo) row.fill(-1);

    auto dfs = [&](auto&& self, int pos, int previous, bool tight) -> ll {
        if (pos == length) return 1;
        if (!tight && memo[pos][previous] != -1) return memo[pos][previous];

        const int boundDigit = digits[pos] - '0';
        const int limit = tight ? boundDigit : 9;
        ll ways = 0;
        for (int digit = 0; digit <= limit; ++digit) {
            if (digit == previous) continue;
            const int next = previous == noPrevious && digit == 0
                                 ? noPrevious : digit;
            ways += self(self, pos + 1, next, tight && digit == boundDigit);
        }
        if (!tight) memo[pos][previous] = ways;
        return ways;
    };
    return dfs(dfs, 0, noPrevious, true);
}
