using ll = long long;

// n 为序列长度且 n >= 1。ranges 中的闭区间下标从 1 开始。
int len = max(1, static_cast<int>(sqrt(n)));
struct Query {
    int l, r, id;
};
vector<Query> ord;
int q = static_cast<int>(ranges.size());
ord.reserve(q);
for (int i = 0; i < q; ++i) {
    auto [l, r] = ranges[i];
    ord.push_back({l, r, i});
}
sort(ord.begin(), ord.end(), [&](const Query& a, const Query& b) {
    int x = (a.l - 1) / len, y = (b.l - 1) / len;
    if (x != y) return x < y;
    return x & 1 ? a.r > b.r : a.r < b.r;
});

// 待填写：初始化空区间的统计状态。
auto add = [&](int i) {
    // 待填写：加入位置 i 并更新区间统计量。
};
auto remove = [&](int i) {
    // 待填写：移除位置 i 并更新区间统计量。
};
auto getAnswer = [&]() -> ll {
    return /* 待填写：从当前区间的统计状态取出答案 */;
};

vector<ll> ans(q);
int l = 1, r = 0;
for (auto [ql, qr, id] : ord) {
    while (l > ql) add(--l);
    while (r < qr) add(++r);
    while (l < ql) remove(l++);
    while (r > qr) remove(r--);
    ans[id] = getAnswer();
}
