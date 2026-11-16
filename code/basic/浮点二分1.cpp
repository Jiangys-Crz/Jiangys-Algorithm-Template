// In solve: long double l, r and eps (l <= r, r - l finite, eps > 0).
// The initial r must be feasible.
auto check = [&](long double x) -> bool {
    // Return true exactly when x satisfies the problem constraints.
    // If x is feasible, every candidate >= x must be feasible.
    return /* TODO: feasibility of x */;
};

while (r - l > eps) {
    long double mid = l + (r - l) / 2;
    if (mid == l || mid == r) break;
    if (check(mid)) r = mid;
    else l = mid;
}
long double ans = r;
