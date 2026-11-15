template<class Check>
long double maxFeasibleReal(long double l, long double r, Check check,
                           long double eps = 1e-8L) {
    while (r - l > eps) {
        long double mid = l + (r - l) / 2;
        if (mid == l || mid == r) break;
        if (check(mid)) l = mid;
        else r = mid;
    }
    return l;
}
