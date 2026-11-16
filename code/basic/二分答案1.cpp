using ll = long long;
using ull = unsigned long long;

// l 和 r 为整数搜索闭区间的端点，满足 l <= r。
// 初始右端点 r 必须可行。
auto check = [&](ll x) -> bool {
    // x 满足题目约束时返回 true，否则返回 false。
    // 若 x 可行，则区间内所有不小于 x 的候选值均须可行。
    return /* 待填写：判定候选值 x 是否可行 */;
};

while (l < r) {
    ull width = ull(r) - ull(l);
    ll mid = l + static_cast<ll>(width / 2);
    if (check(mid)) r = mid;
    else l = mid + 1;
}
ll ans = l;
