#include <vector>

using ll = long long;

ll countInversions(std::vector<int>& a) {
    std::vector<int> buffer(a.size());
    auto solve = [&](auto&& self, int l, int r) -> ll {
        if (r - l <= 1) {
            return 0;
        }
        int mid = l + (r - l) / 2;
        ll count = self(self, l, mid) + self(self, mid, r);
        int i = l, j = mid, k = l;
        while (i < mid && j < r) {
            if (a[i] <= a[j]) {
                buffer[k++] = a[i++];
            } else {
                count += mid - i;
                buffer[k++] = a[j++];
            }
        }
        while (i < mid) {
            buffer[k++] = a[i++];
        }
        while (j < r) {
            buffer[k++] = a[j++];
        }
        for (int p = l; p < r; ++p) {
            a[p] = buffer[p];
        }
        return count;
    };
    return solve(solve, 0, static_cast<int>(a.size()));
}
