#include <optional>

#include "dsu.hpp"

struct ParityConstraints {
    int n;
    DSU dsu;

    explicit ParityConstraints(int n) : n(n), dsu(2 * n) {}

    bool add(int u, int v, bool different) {
        if (different) {
            if (dsu.same(u, v)) return false;
            dsu.merge(u, v + n);
            dsu.merge(u + n, v);
        } else {
            if (dsu.same(u, v + n)) return false;
            dsu.merge(u, v);
            dsu.merge(u + n, v + n);
        }
        return true;
    }

    std::optional<bool> relation(int u, int v) {
        if (dsu.same(u, v)) return false;
        if (dsu.same(u, v + n)) return true;
        return std::nullopt;
    }
};
