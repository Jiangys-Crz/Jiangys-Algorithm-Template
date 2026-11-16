using ull = unsigned long long;

// a、b、m 为无符号整数，且 m > 0。ans 为 a 与 b 的乘积模 m。

a %= m;
b %= m;
ull ans = 0;
while (b) {
    if (b & 1) ans = ans >= m - a ? ans - (m - a) : ans + a;
    a = a >= m - a ? a - (m - a) : a + a;
    b >>= 1;
}
