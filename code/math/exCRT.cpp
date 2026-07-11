i64 EXCRT(int k, std::vector<i64>&r, std::vector<i64>&c) {
    i64 c1, c2, r1, r2, p, q;
    c1 = c[1], r1 = r[1];
    for (int i = 2; i <= k; i++) {
        c2 = c[i], r2 = r[i];
        i64 d = exgcd(c1, c2, p, q);
        if ((r2 - r1) % d) {
            return -1; // 无解
        }
        p = p * (r2 - r1) / d;
        p = (p % (c2 / d) + (c2 / d)) % (c2 / d);
        r1 = c1 * p + r1;
        c1 = c1 * c2 / d;
    }
    return (r1 % c1 + c1) % c1;
}