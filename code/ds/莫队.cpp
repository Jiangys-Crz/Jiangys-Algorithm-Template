#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

using ll = long long;

std::vector<int> moDistinct(
    const std::vector<ll>& a,
    const std::vector<std::pair<int, int>>& ranges) {
    int n = static_cast<int>(a.size()) - 1;
    int len = std::max(1, static_cast<int>(std::sqrt(n)));
    std::vector<ll> val(a.begin() + 1, a.end());
    std::sort(val.begin(), val.end());
    val.erase(std::unique(val.begin(), val.end()), val.end());

    std::vector<int> rank(n + 1);
    for (int i = 1; i <= n; ++i) {
        rank[i] = static_cast<int>(
            std::lower_bound(val.begin(), val.end(), a[i]) - val.begin());
    }

    struct Query {
        int l, r, id;
    };
    int q = static_cast<int>(ranges.size());
    std::vector<Query> ord;
    for (int i = 0; i < q; ++i) {
        auto [l, r] = ranges[i];
        ord.push_back({l, r, i});
    }
    std::sort(ord.begin(), ord.end(), [&](const Query& a, const Query& b) {
        int x = (a.l - 1) / len, y = (b.l - 1) / len;
        if (x != y) return x < y;
        return x & 1 ? a.r > b.r : a.r < b.r;
    });

    std::vector<int> cnt(val.size()), ans(q);
    int l = 1, r = 0, distinct = 0;
    auto add = [&](int i) {
        if (++cnt[rank[i]] == 1) ++distinct;
    };
    auto del = [&](int i) {
        if (--cnt[rank[i]] == 0) --distinct;
    };
    for (auto [ql, qr, id] : ord) {
        while (l > ql) add(--l);
        while (r < qr) add(++r);
        while (l < ql) del(l++);
        while (r > qr) del(r--);
        ans[id] = distinct;
    }
    return ans;
}
