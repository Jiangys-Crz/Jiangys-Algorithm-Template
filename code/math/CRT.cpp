i64 CRT(int k, std::vector<i64>&r, std::vector<i64>&c) {
    i64 n = 1, ans = 0;
    for (int i = 1; i <= k; i++) n = n * c[i];
    for (int i = 1; i <= k; i++) {
        i64 m = n / c[i], b, y;
        exgcd(m, c[i], b, y); // m * b = 1(mod c[i]);  => m*b + c[i]*y = 1
        ans = (ans + r[i] * m * b % n) % n;
    }
    return (ans % n + n) % n;
}