#include <iostream>
#include <cstddef>
#include <functional>
#include <queue>
#include <tuple>
#include <vector>

using ll = long long;

int main() {
    std::size_t k;
    if (!(std::cin >> k)) return 0;
    std::vector<std::vector<ll>> a(k);
    for (auto& row : a) {
        std::size_t n;
        std::cin >> n;
        row.resize(n);
        for (ll& x : row) std::cin >> x;
    }

    using State = std::tuple<ll, std::size_t, std::size_t>;
    std::priority_queue<State, std::vector<State>, std::greater<>> pq;
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (!a[i].empty()) pq.push({a[i][0], i, 0});
    }

    while (!pq.empty()) {
        auto [x, i, j] = pq.top();
        pq.pop();
        std::cout << x << ' ';
        if (j + 1 < a[i].size()) pq.push({a[i][j + 1], i, j + 1});
    }
    std::cout << '\n';
}
