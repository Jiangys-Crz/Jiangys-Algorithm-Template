#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using uint = unsigned int;
using ll = long long;

int main() {
    uint seed;
    int n;
    ll l, r;
    if (!(std::cin >> seed >> n >> l >> r)) return 0;
    std::mt19937 rng(seed);

    std::uniform_int_distribution<ll> pick(l, r);
    for (int i = 1; i <= n; ++i) {
        std::cout << pick(rng) << (i == n ? '\n' : ' ');
    }

    std::vector<int> id(n);
    std::iota(id.begin(), id.end(), 1LL);
    std::shuffle(id.begin(), id.end(), rng);
    for (int i = 0; i < n; ++i) {
        std::cout << id[i] << (i + 1 == n ? '\n' : ' ');
    }

    for (int i = 1; i < n; ++i) {
        int p = std::uniform_int_distribution<int>(0, i - 1)(rng);
        std::cout << id[p] << ' ' << id[i] << '\n';
    }
}
