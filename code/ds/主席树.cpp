#include <algorithm>
#include <optional>
#include <vector>

using ll = long long;

struct PersistentKth {
    struct Node {
        int l = 0, r = 0, cnt = 0;
    };

    std::vector<ll> val;
    std::vector<Node> tr{Node{}};
    std::vector<int> root;

    explicit PersistentKth(const std::vector<ll>& a)
        : val(a.begin() + 1, a.end()), root(a.size()) {
        std::sort(val.begin(), val.end());
        val.erase(std::unique(val.begin(), val.end()), val.end());
        for (int i = 1; i < static_cast<int>(a.size()); ++i) {
            int pos = static_cast<int>(
                std::lower_bound(val.begin(), val.end(), a[i]) - val.begin());
            root[i] = insert(root[i - 1], 0, static_cast<int>(val.size()) - 1, pos);
        }
    }

    std::optional<ll> kth(int l, int r, int k) const {
        if (k <= 0 || k > r - l + 1) return std::nullopt;
        int x = root[l - 1], y = root[r];
        int lo = 0, hi = static_cast<int>(val.size()) - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            int left = tr[tr[y].l].cnt - tr[tr[x].l].cnt;
            if (k <= left) {
                x = tr[x].l;
                y = tr[y].l;
                hi = mid;
            } else {
                x = tr[x].r;
                y = tr[y].r;
                lo = mid + 1;
                k -= left;
            }
        }
        return val[lo];
    }

private:
    int insert(int u, int l, int r, int pos) {
        Node old = tr[u];
        int v = static_cast<int>(tr.size());
        tr.push_back(old);
        ++tr[v].cnt;
        if (l == r) return v;
        int mid = l + (r - l) / 2;
        if (pos <= mid) tr[v].l = insert(old.l, l, mid, pos);
        else tr[v].r = insert(old.r, mid + 1, r, pos);
        return v;
    }
};
