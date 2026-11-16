using ull = unsigned long long;
using ulll = unsigned __int128;

// a、b、m 为无符号整数，且 m > 0。ans 为 a 的 b 次幂模 m。

ull ans = 1 % m;
a %= m;
while (b) {
    if (b & 1) ans = ulll(ans) * a % m;
    a = ulll(a) * a % m;
    b >>= 1;
}
