using ull = unsigned long long;

// In solve: ull n >= 1. phi is Euler's totient of n.
ull x = n, phi = n;
for (ull p = 2; p <= x / p; p += p == 2 ? 1 : 2) {
    if (x % p) continue;
    phi -= phi / p;
    do {
        x /= p;
    } while (x % p == 0);
}
if (x > 1) phi -= phi / x;
