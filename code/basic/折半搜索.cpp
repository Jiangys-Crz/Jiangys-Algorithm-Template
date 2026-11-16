#include <algorithm>
#include <cstddef>
#include <vector>

using ll = long long;

// In solve: vector<int> a and ll target; count fits in ll.

ll minSum = 0, maxSum = 0;
for (int value : a) {
    minSum += std::min(value, 0);
    maxSum += std::max(value, 0);
}

auto sums = [&](int l, int r) {
    std::vector<ll> result{0};
    for (int i = l; i < r; ++i) {
        std::size_t oldSize = result.size();
        for (std::size_t j = 0; j < oldSize; ++j) {
            result.push_back(result[j] + a[i]);
        }
    }
    return result;
};

int n = static_cast<int>(a.size());
ll count = 0;
if (minSum <= target && target <= maxSum) {
    auto left = sums(0, n / 2);
    auto right = sums(n / 2, n);
    std::sort(right.begin(), right.end());
    for (ll sum : left) {
        auto [first, last] = std::equal_range(right.begin(), right.end(), target - sum);
        count += last - first;
    }
}
