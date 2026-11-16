// In solve: long double l, r and eps (l <= r, r - l finite, eps > 0).
auto calc = [&](long double x) -> long double {
    // Return the objective value at x. To minimize, its shape on [l, r]
    // must be strictly decreasing, then strictly increasing.
    return /* TODO: objective value at x */;
};

while (r - l > eps) {
    long double m1 = l + (r - l) / 3;
    long double m2 = r - (r - l) / 3;
    if (m1 == l || m2 == r || m1 >= m2) break;
    if (calc(m1) > calc(m2)) l = m1;
    else r = m2;
}
long double pos = l + (r - l) / 2;
