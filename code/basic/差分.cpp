#include <vector>

#include "../types.hpp"

std::vector<ll> buildDifference(const std::vector<int>& a) {
    int n = static_cast<int>(a.size());
    std::vector<ll> diff(n + 2, 0);
    ll prev = 0;
    for (int i = 1; i <= n; ++i) {
        diff[i] = a[i - 1] - prev;
        prev = a[i - 1];
    }
    return diff;
}

void addRange(std::vector<ll>& diff, int l, int r, ll delta) {
    diff[l] += delta;
    diff[r + 1] -= delta;
}

std::vector<ll> restoreArray(const std::vector<ll>& diff) {
    int n = static_cast<int>(diff.size()) - 2;
    std::vector<ll> a(n);
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += diff[i];
        a[i - 1] = sum;
    }
    return a;
}
