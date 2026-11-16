using ull = unsigned long long;
using ulll = unsigned __int128;

// In solve: ull a, b, m with m > 0. ans is a^b mod m.

ull ans = 1 % m;
a %= m;
while (b) {
    if (b & 1) ans = ulll(ans) * a % m;
    a = ulll(a) * a % m;
    b >>= 1;
}
