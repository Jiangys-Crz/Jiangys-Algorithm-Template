#include <iostream>
#include <algorithm>
#include <cstddef>
#include <vector>

using ll = long long;

int main() {
    int n;
    ll target;
    if (!(std::cin >> n >> target)) return 0;
    std::vector<int> a(n);
    for (int& x : a) std::cin >> x;

    ll minSum = 0, maxSum = 0;
    for (int value : a) {
        minSum += std::min(value, 0);
        maxSum += std::max(value, 0);
    }
    if (target < minSum || target > maxSum) {
        std::cout << "0\n";
        return 0;
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

    auto left = sums(0, n / 2);
    auto right = sums(n / 2, n);
    std::sort(right.begin(), right.end());

    ll count = 0;
    for (ll sum : left) {
        auto [first, last] = std::equal_range(right.begin(), right.end(), target - sum);
        count += last - first;
    }
    std::cout << count << '\n';
}
