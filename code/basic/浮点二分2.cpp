// 先给定实数闭区间 [l, r] 和容差 eps，要求区间宽度有限且 eps > 0。
// 初始左端点 l 必须可行。
auto check = [&](long double x) -> bool {
    // x 满足题目约束时返回 true，否则返回 false。
    // 若 x 可行，则区间内所有不大于 x 的候选值均须可行。
    return /* 待填写：判定候选值 x 是否可行 */;
};

while (r - l > eps) {
    long double mid = l + (r - l) / 2;
    if (mid == l || mid == r) break;
    if (check(mid)) l = mid;
    else r = mid;
}
long double ans = l;
