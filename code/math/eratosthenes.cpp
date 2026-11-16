using ll = long long;

// n 为非负整数。primes 保存不超过 n 的全部质数。

vector<bool> st(n + 1);
for (int p = 2; p <= n / p; ++p) {
    if (st[p]) continue;
    for (ll j = 1LL * p * p; j <= n; j += p) st[j] = true;
}
vector<int> primes;
for (int i = 2; i <= n; ++i) {
    if (!st[i]) primes.push_back(i);
}
