template<class Calc>
long double ternaryMaximum(long double l, long double r, Calc calc,
                           long double eps = 1e-8L) {
    while (r - l > eps) {
        long double third = (r - l) / 3;
        long double m1 = l + third, m2 = r - third;
        if (m1 == l || m2 == r || m1 >= m2) break;
        if (calc(m1) < calc(m2)) l = m1;
        else r = m2;
    }
    return l + (r - l) / 2;
}
