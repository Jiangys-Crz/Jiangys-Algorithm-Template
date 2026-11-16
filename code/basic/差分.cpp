using ll = long long;

// 原数组下标为 1 至 n，令 a[0] = 0。
// updates 保存每次操作的闭区间 [l, r] 和增量 delta。
vector<ll> d(n + 2);
for (int i = 1; i <= n; ++i) d[i] = a[i] - a[i - 1];

for (auto [l, r, delta] : updates) {
    d[l] += delta;
    d[r + 1] -= delta;
}
for (int i = 1; i <= n; ++i) d[i] += d[i - 1];
// d[1..n] 保存更新后的序列。
