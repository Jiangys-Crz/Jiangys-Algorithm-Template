using ull = unsigned long long;

// n 为正整数。phi 为 n 的欧拉函数值。
ull x = n, phi = n;
for (ull p = 2; p <= x / p; p += p == 2 ? 1 : 2) {
    if (x % p) continue;
    phi -= phi / p;
    do {
        x /= p;
    } while (x % p == 0);
}
if (x > 1) phi -= phi / x;
