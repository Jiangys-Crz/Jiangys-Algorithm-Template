#include <algorithm>
#include <cstddef>
#include <vector>

long long countSubsetsWithSum(const std::vector<int>& a, long long target) {
    long long minSum = 0, maxSum = 0;
    for (int value : a) {
        minSum += std::min(value, 0);
        maxSum += std::max(value, 0);
    }
    if (target < minSum || target > maxSum) {
        return 0;
    }

    auto sums = [&](int l, int r) {
        std::vector<long long> result{0};
        for (int i = l; i < r; ++i) {
            std::size_t oldSize = result.size();
            for (std::size_t j = 0; j < oldSize; ++j) {
                result.push_back(result[j] + a[i]);
            }
        }
        return result;
    };

    int n = static_cast<int>(a.size());
    auto left = sums(0, n / 2);
    auto right = sums(n / 2, n);
    std::sort(right.begin(), right.end());

    long long count = 0;
    for (long long sum : left) {
        auto [first, last] = std::equal_range(right.begin(), right.end(), target - sum);
        count += last - first;
    }
    return count;
}
