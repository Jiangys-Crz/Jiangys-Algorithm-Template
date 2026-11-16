#include <algorithm>
#include <string_view>
#include <utility>
#include <vector>

#ifndef XCPC_STRING_MANACHER_HPP
#define XCPC_STRING_MANACHER_HPP

struct Manacher {
    vector<int> odd, even;

    explicit Manacher(string_view s) : odd(s.size()), even(s.size()) {
        int n = static_cast<int>(s.size());
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = i > r ? 1 : min(odd[l + (r - i)], r - i + 1);
            while (k <= i && k < n - i && s[i - k] == s[i + k]) ++k;
            odd[i] = k;
            if (i + k - 1 > r) {
                l = i - k + 1;
                r = i + k - 1;
            }
        }
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = i > r ? 0 : min(even[l + (r - i) + 1], r - i + 1);
            while (k < i && k < n - i && s[i - k - 1] == s[i + k]) ++k;
            even[i] = k;
            if (i + k - 1 > r) {
                l = i - k;
                r = i + k - 1;
            }
        }
    }

    bool isPalindrome(int l, int r) const {
        if (l == r) return true;
        int k = (r - l) / 2, mid = l + k;
        return (r - l) % 2 ? odd[mid] >= k + 1 : even[mid] >= k;
    }

    pair<int, int> longest() const {
        int l = 0, r = 0;
        auto consider = [&](int x, int y) {
            if (y - x > r - l || (y - x == r - l && x < l)) {
                l = x;
                r = y;
            }
        };
        for (int i = 0; i < static_cast<int>(odd.size()); ++i) {
            consider(i - odd[i] + 1, i + odd[i]);
            consider(i - even[i], i + even[i]);
        }
        return {l, r};
    }
};

#endif
