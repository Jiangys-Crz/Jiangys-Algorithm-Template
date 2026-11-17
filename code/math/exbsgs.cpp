ll exbsgs(ll a, ll b, ll p) {
    a %= p, b %= p;
    if (b == 1 || p == 1) return 0;
    ll d, k = 0, A = 1;
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
    ll m = std::ceil(std::sqrt(p));
    ll t = b;
    std::unordered_map<ll, ll> mp;
    mp[b] = 0;
    for (int j = 1; j < m; j++) {
        t = t * a % p;
        mp[t] = j;
    }
    ll mi = 1;
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