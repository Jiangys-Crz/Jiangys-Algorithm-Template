#pragma once

#include <cassert>
#include <cstddef>
#include <vector>

template<class T>
struct Fenwick {
    int n;
    std::vector<T> f;

    explicit Fenwick(int n) : n(n), f(n + 1) {}

    void add(int x, T val) {
        assert(1 <= x && x <= n);
        for (std::size_t i = x; i < f.size(); i += i & -i) f[i] += val;
    }

    T query(int x) const {
        T res{};
        for (int i = x; i; i -= i & -i) res += f[i];
        return res;
    }

    T rangesum(int l, int r) const {
        return l > r ? T{} : query(r) - query(l - 1);
    }

    int kth(T k) const {
        if (k <= T{} || k > query(n)) return 0;
        int step = 1, x = 0;
        while (step <= n / 2) step *= 2;
        for (; step; step /= 2) {
            if (step > n - x || f[x + step] >= k) continue;
            x += step;
            k -= f[x];
        }
        return x + 1;
    }
};
