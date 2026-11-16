#ifndef XCPC_STRING_SUFFIX_ARRAY_HPP
#define XCPC_STRING_SUFFIX_ARRAY_HPP

struct SuffixArray {
    vector<int> sa, rk, height;

    explicit SuffixArray(string_view s)
        : sa(s.size()), rk(s.size()), height(s.size()) {
        int n = static_cast<int>(s.size());
        if (!n) return;

        vector<int> ord(n), id(n), nxt(n), cnt(max(n, 256) + 1);
        auto sortByFirst = [&](int classes) {
            fill(cnt.begin(), cnt.begin() + classes + 1, 0);
            for (int x : ord) ++cnt[id[x]];
            for (int i = 1; i <= classes; ++i) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i) {
                int u = ord[i];
                sa[--cnt[id[u]]] = u;
            }
        };
        iota(ord.begin(), ord.end(), 0);
        for (int i = 0; i < n; ++i) id[i] = static_cast<unsigned char>(s[i]) + 1;
        int classes = 256;
        sortByFirst(classes);
        for (int k = 1; k < n; ) {
            int pos = 0;
            for (int i = n - k; i < n; ++i) ord[pos++] = i;
            for (int i : sa) {
                if (i >= k) ord[pos++] = i - k;
            }
            sortByFirst(classes);

            classes = 1;
            nxt[sa[0]] = 1;
            auto second = [&](int u) { return u < n - k ? id[u + k] : 0; };
            for (int i = 1; i < n; ++i) {
                int x = sa[i - 1], y = sa[i];
                if (id[x] != id[y] || second(x) != second(y)) ++classes;
                nxt[y] = classes;
            }
            id.swap(nxt);
            if (classes == n || k >= n - k) break;
            k *= 2;
        }

        for (int i = 0; i < n; ++i) rk[sa[i]] = i;
        for (int i = 0, h = 0; i < n; ++i) {
            if (!rk[i]) {
                h = 0;
                continue;
            }
            int j = sa[rk[i] - 1];
            while (h < n - i && h < n - j && s[i + h] == s[j + h]) ++h;
            height[rk[i]] = h;
            if (h) --h;
        }
    }
};

#endif
