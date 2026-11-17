ll bsgs(ll a, ll b, ll p) {
    a %= p, b %= p;
    if (b == 1) return 0;
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
    t = 1;
    for (int i = 1; i <= m; i++) {
        t = t * mi % p;
        if (mp.count(t)) {
            return i * m - mp[t];
        }
    }
    return -1;
}