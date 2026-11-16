using ll = long long;

// a 保存半开区间 [l, r)，且 l < r。

sort(a.begin(), a.end(), [](const auto& x, const auto& y) {
    return x.second < y.second;
});

int ans = 0;
ll last = numeric_limits<ll>::min();
for (auto [l, r] : a) {
    if (l >= last) {
        ++ans;
        last = r;
    }
}
