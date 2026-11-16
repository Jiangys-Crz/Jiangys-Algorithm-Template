using ull = unsigned long long;

// In solve: ull a, b, m with m > 0. ans is a*b mod m.

a %= m;
b %= m;
ull ans = 0;
while (b) {
    if (b & 1) ans = ans >= m - a ? ans - (m - a) : ans + a;
    a = a >= m - a ? a - (m - a) : a + a;
    b >>= 1;
}
