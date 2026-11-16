#include <algorithm>
#include <utility>
#include <vector>

using ll = long long;

#ifndef XCPC_MATH_LINEAR_SIEVE_HPP
#define XCPC_MATH_LINEAR_SIEVE_HPP

struct LinearSieve {
    vector<int> primes, lp, phi, mu;

    explicit LinearSieve(int n) : lp(n + 1), phi(n + 1), mu(n + 1) {
        if (n >= 1) phi[1] = mu[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (!lp[i]) {
                primes.push_back(i);
                lp[i] = i;
                phi[i] = i - 1;
                mu[i] = -1;
            }
            for (int p : primes) {
                if (p > n / i) break;
                int x = i * p;
                lp[x] = p;
                if (p == lp[i]) {
                    phi[x] = phi[i] * p;
                    mu[x] = 0;
                    break;
                }
                phi[x] = phi[i] * (p - 1);
                mu[x] = -mu[i];
            }
        }
    }

    vector<pair<int, int>> factor(int x) const {
        vector<pair<int, int>> res;
        while (x > 1) {
            int p = lp[x], e = 0;
            do {
                x /= p;
                ++e;
            } while (x % p == 0);
            res.push_back({p, e});
        }
        return res;
    }
};

#endif

#ifndef XCPC_MATH_MOBIUS_HPP
#define XCPC_MATH_MOBIUS_HPP

struct MobiusPrefix {
    vector<int> pre;

    explicit MobiusPrefix(const LinearSieve& sieve) : pre(sieve.mu.size()) {
        for (size_t i = 1; i < pre.size(); ++i) {
            pre[i] = pre[i - 1] + sieve.mu[i];
        }
    }

    ll countCoprimePairs(int n, int m) const {
        ll res = 0;
        int end = min(n, m);
        for (int l = 1; l <= end; ) {
            int x = n / l, y = m / l;
            int r = min(n / x, m / y);
            res += ll(pre[r] - pre[l - 1]) * x * y;
            if (r == end) break;
            l = r + 1;
        }
        return res;
    }
};

#endif
