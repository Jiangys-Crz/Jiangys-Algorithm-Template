#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

using ll = long long;

// In solve: int n >= 1; ranges contains 1-based closed intervals.
int len = std::max(1, static_cast<int>(std::sqrt(n)));
struct Query {
    int l, r, id;
};
std::vector<Query> ord;
int q = static_cast<int>(ranges.size());
ord.reserve(q);
for (int i = 0; i < q; ++i) {
    auto [l, r] = ranges[i];
    ord.push_back({l, r, i});
}
std::sort(ord.begin(), ord.end(), [&](const Query& a, const Query& b) {
    int x = (a.l - 1) / len, y = (b.l - 1) / len;
    if (x != y) return x < y;
    return x & 1 ? a.r > b.r : a.r < b.r;
});

// TODO: Initialize the statistic for the empty interval.
auto add = [&](int i) {
    // TODO: Insert position i and update the statistic.
};
auto remove = [&](int i) {
    // TODO: Erase position i and update the statistic.
};
auto getAnswer = [&]() -> ll {
    return /* TODO: answer for the current interval */;
};

std::vector<ll> ans(q);
int l = 1, r = 0;
for (auto [ql, qr, id] : ord) {
    while (l > ql) add(--l);
    while (r < qr) add(++r);
    while (l < ql) remove(l++);
    while (r > qr) remove(r--);
    ans[id] = getAnswer();
}
