using ll = long long;

class RangeBlocks {
public:
    explicit RangeBlocks(vector<ll> a)
        : n(static_cast<int>(a.size()) - 1),
          len(max(1, static_cast<int>(sqrt(n)))),
          a(move(a)), sum((n - 1) / len + 1), tag(sum.size()) {
        for (int i = 1; i <= n; ++i) sum[bel(i)] += this->a[i];
    }

    void modify(int l, int r, ll val) {
        for (int b = bel(l); b <= bel(r); ++b) {
            auto [lo, hi] = bounds(b);
            int x = max(lo, l), y = min(hi, r);
            if (x == lo && y == hi) {
                tag[b] += val;
            } else {
                for (int i = x; i <= y; ++i) a[i] += val;
                sum[b] += (y - x + 1) * val;
            }
        }
    }

    ll query(int l, int r) const {
        ll ans = 0;
        for (int b = bel(l); b <= bel(r); ++b) {
            auto [lo, hi] = bounds(b);
            int x = max(lo, l), y = min(hi, r);
            if (x == lo && y == hi) ans += sum[b];
            else for (int i = x; i <= y; ++i) ans += a[i];
            ans += (y - x + 1) * tag[b];
        }
        return ans;
    }

private:
    int n, len;
    vector<ll> a, sum, tag;

    int bel(int i) const {
        return (i - 1) / len;
    }

    pair<int, int> bounds(int b) const {
        int l = b * len + 1;
        return {l, l + min(n - l, len - 1)};
    }
};
