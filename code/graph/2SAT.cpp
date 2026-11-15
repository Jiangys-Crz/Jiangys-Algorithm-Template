#include <optional>

#include "scc.hpp"

struct TwoSAT {
    int n;
    Graph g;

    explicit TwoSAT(int n) : n(n), g(2 * n) {}

    static int lit(int x, bool value) {
        return 2 * x - !value;
    }

    static int neg(int p) {
        return p % 2 ? p + 1 : p - 1;
    }

    void addClause(int x, bool a, int y, bool b) {
        int p = lit(x, a), q = lit(y, b);
        g.addEdge(neg(p), q);
        g.addEdge(neg(q), p);
    }

    std::optional<std::vector<char>> work() const {
        SCC scc(g);
        std::vector<char> ans(n + 1);
        for (int x = 1; x <= n; ++x) {
            int p = lit(x, true), q = lit(x, false);
            if (scc.bel[p] == scc.bel[q]) return std::nullopt;
            ans[x] = scc.bel[p] < scc.bel[q];
        }
        return ans;
    }
};
