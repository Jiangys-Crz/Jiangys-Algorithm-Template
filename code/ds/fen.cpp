template <class T>
struct Fenwick {
    const int N;
    std::vector<T> f;
    Fenwick(int _) : N(_), f(_ + 10) {}

    void add(int x, const T v) {
        for (int i = x; i <= N; i += (i & -i)) {
            f[i] += v;
        }
    }

    T query(int x) {
        if (x > N || x <= 0) {
            return T(0ULL);
        }

        T res = 0ULL;
        for (int i = x; i; i -= (i & -i)) {
            res += f[i];
        }
        return res;
    }

    T rangesum(int l, int r) {
        if (l > r) {
            return T(0ULL);
        }

        return query(r) - query(l - 1);
    }

    int kth(int k) {
        int x = 0;
        for (int i = 1 << 20; i; i >>= 1) {
            int nx = x + i;
            if (nx <= N && f[nx] < k) {
                x = nx;
                k -= f[nx];
            }
        }
        return x + 1;
    }
};