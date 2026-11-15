#include <cstdint>

#include "tree.hpp"

struct TreeXor {
    std::vector<std::uint64_t> a, pre;

    TreeXor(const Tree& tr, const std::vector<std::uint64_t>& value)
        : a(value), pre(tr.n + 1) {
        for (int i = 1; i <= tr.n; ++i) {
            int u = tr.id[i];
            pre[u] = pre[tr.fa[u]] ^ a[u];
        }
    }

    std::uint64_t nodeXor(int u, int v, int p) const {
        return pre[u] ^ pre[v] ^ a[p];
    }

    std::uint64_t edgeXor(int u, int v) const {
        return pre[u] ^ pre[v];
    }
};
