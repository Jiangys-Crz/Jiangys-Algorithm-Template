#include "../types.hpp"
#include "tree.hpp"

struct TreeDifference {
    const Tree& tr;
    std::vector<ll> d;

    explicit TreeDifference(const Tree& tr) : tr(tr), d(tr.n + 1) {}

    void addNodes(int u, int v, int p, ll val) {
        d[u] += val;
        d[v] += val;
        d[p] -= val;
        if (tr.fa[p]) d[tr.fa[p]] -= val;
    }

    void addEdges(int u, int v, int p, ll val) {
        d[u] += val;
        d[v] += val;
        d[p] -= 2 * val;
    }

    std::vector<ll> collect() const {
        auto res = d;
        for (int i = tr.n; i >= 2; --i) {
            int u = tr.id[i];
            res[tr.fa[u]] += res[u];
        }
        return res;
    }
};
