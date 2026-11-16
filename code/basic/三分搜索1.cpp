// 先给定实数闭区间 [l, r] 和容差 eps，要求区间宽度有限且 eps > 0。
auto calc = [&](long double x) -> long double {
    // 返回候选位置 x 的目标函数值。
    // 求最大值时，目标函数在 [l, r] 上先严格递增，后严格递减。
    return /* 待填写：x 处的目标函数值 */;
};

while (r - l > eps) {
    long double m1 = l + (r - l) / 3;
    long double m2 = r - (r - l) / 3;
    if (m1 == l || m2 == r || m1 >= m2) break;
    if (calc(m1) < calc(m2)) l = m1;
    else r = m2;
}
long double pos = l + (r - l) / 2;
