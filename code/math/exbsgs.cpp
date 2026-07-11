i64 exbsgs(i64 a, i64 b, i64 p) {
    a %= p, b %= p;
    if (b == 1 || p == 1) return 0;
    i64 d, k = 0, A = 1;
    while (true) {
        d = std::gcd(a, p);
        if (d == 1) break;
        if (b % d) {
            return -1;
        }
        k++;
        b /= d;
        p /= d;
        A = A * (a / d) % p;
        if (A == b) {
            return k;
        }
    }
    i64 m = std::ceil(std::sqrt(p));
    i64 t = b;
    std::unordered_map<i64, i64> mp;
    mp[b] = 0;
    for (int j = 1; j < m; j++) {
        t = t * a % p;
        mp[t] = j;
    }
    i64 mi = 1;
    for (int i = 1; i <= m; i++) {
        mi = mi * a % p;
    }
    t = A;
    for (int i = 1; i <= m; i++) {
        t = t * mi % p;
        if (mp.count(t)) {
            return i * m - mp[t] + k;
        }
    }
    return -1;
}