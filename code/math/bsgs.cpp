i64 bsgs(i64 a, i64 b, i64 p) {
    a %= p, b %= p;
    if (b == 1) return 0;
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
    t = 1;
    for (int i = 1; i <= m; i++) {
        t = t * mi % p;
        if (mp.count(t)) {
            return i * m - mp[t];
        }
    }
    return -1;
}