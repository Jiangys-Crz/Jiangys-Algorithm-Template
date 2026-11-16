#include <cstddef>
#include <functional>
#include <queue>
#include <tuple>
#include <vector>

using ll = long long;

// In solve: a is a list of nondecreasing sequences.

using State = std::tuple<ll, std::size_t, std::size_t>;
std::priority_queue<State, std::vector<State>, std::greater<>> pq;
for (std::size_t i = 0; i < a.size(); ++i) {
    if (!a[i].empty()) pq.push({a[i][0], i, 0});
}

while (!pq.empty()) {
    auto [x, i, j] = pq.top();
    pq.pop();
    // TODO: Consume the next value x in the merged order.
    if (j + 1 < a[i].size()) pq.push({a[i][j + 1], i, j + 1});
}
