using ull = unsigned long long;

// n 为正整数。factors 保存各质因子及其指数。
ull x = n;
vector<pair<ull, int>> factors;
for (ull p = 2; p <= x / p; p += p == 2 ? 1 : 2) {
    if (x % p) continue;
    int e = 0;
    do {
        x /= p;
        ++e;
    } while (x % p == 0);
    factors.emplace_back(p, e);
}
if (x > 1) factors.emplace_back(x, 1);
