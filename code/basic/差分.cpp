#include <vector>

std::vector<long long> buildDifference(const std::vector<int>& a) {
    int n = static_cast<int>(a.size());
    std::vector<long long> diff(n + 2, 0);
    long long prev = 0;
    for (int i = 1; i <= n; ++i) {
        diff[i] = a[i - 1] - prev;
        prev = a[i - 1];
    }
    return diff;
}

void addRange(std::vector<long long>& diff, int l, int r, long long delta) {
    diff[l] += delta;
    diff[r + 1] -= delta;
}

std::vector<long long> restoreArray(const std::vector<long long>& diff) {
    int n = static_cast<int>(diff.size()) - 2;
    std::vector<long long> a(n);
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += diff[i];
        a[i - 1] = sum;
    }
    return a;
}
