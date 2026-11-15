#pragma once

#include <algorithm>
#include <utility>
#include <vector>

#include "comb.hpp"

template<class Z>
Z countGridPaths(int n, int m, std::vector<std::pair<int, int>> blocks,
                 const Comb<Z>& comb) {
    const std::pair<int, int> target{n, m};
    std::sort(blocks.begin(), blocks.end());
    blocks.erase(std::unique(blocks.begin(), blocks.end()), blocks.end());
    if (!blocks.empty() && blocks.back() == target) return 0;
    blocks.push_back(target);

    std::vector<Z> dp(blocks.size());
    for (std::size_t i = 0; i < blocks.size(); ++i) {
        auto [x, y] = blocks[i];
        dp[i] = comb.C((x - 1) + (y - 1), x - 1);
        for (std::size_t j = 0; j < i; ++j) {
            auto [u, v] = blocks[j];
            if (v > y) continue;
            dp[i] -= dp[j] * comb.C((x - u) + (y - v), x - u);
        }
    }
    return dp.back();
}
