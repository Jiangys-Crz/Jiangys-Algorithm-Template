ll CRT(int k, std::vector<ll>&r, std::vector<ll>&c) {
    ll n = 1, ans = 0;
    for (int i = 1; i <= k; i++) n = n * c[i];
    for (int i = 1; i <= k; i++) {
        ll m = n / c[i], b, y;
        exgcd(m, c[i], b, y); // m * b = 1(mod c[i]);  => m*b + c[i]*y = 1
        ans = (ans + r[i] * m * b % n) % n;
    }
    return (ans % n + n) % n;
}