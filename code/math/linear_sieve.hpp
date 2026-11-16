#include <utility>
#include <vector>

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
