#include <cstddef>
#include <functional>
#include <queue>
#include <tuple>
#include <vector>

#include "../types.hpp"

std::vector<ll> mergeSorted(
    const std::vector<std::vector<ll>>& a) {
    using State = std::tuple<ll, std::size_t, std::size_t>;
    std::priority_queue<State, std::vector<State>, std::greater<>> pq;
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (!a[i].empty()) pq.push({a[i][0], i, 0});
    }

    std::vector<ll> res;
    while (!pq.empty()) {
        auto [x, i, j] = pq.top();
        pq.pop();
        res.push_back(x);
        if (j + 1 < a[i].size()) pq.push({a[i][j + 1], i, j + 1});
    }
    return res;
}
