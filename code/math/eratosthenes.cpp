#include <vector>

using ll = long long;

std::vector<int> eratosthenes(int n) {
    std::vector<bool> st(n + 1);
    for (int p = 2; p <= n / p; ++p) {
        if (st[p]) continue;
        for (ll j = 1LL * p * p; j <= n; j += p) st[j] = true;
    }
    std::vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) primes.push_back(i);
    }
    return primes;
}
