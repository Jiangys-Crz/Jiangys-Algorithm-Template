std::vector<i64> inv;

void mod_inverse(i64 n, i64 p) {
    inv.resize(n + 1);
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (p - p / i) * inv[p % i] % p;
    }
}