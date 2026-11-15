#include "tree.hpp"

struct EulerTour {
    std::vector<int> id, first;

    explicit EulerTour(const Tree& tr) : first(tr.n + 1) {
        std::vector<int> stk{tr.root};
        id.push_back(tr.root);
        for (int i = 2; i <= tr.n; ++i) {
            int u = tr.id[i];
            while (stk.back() != tr.fa[u]) {
                stk.pop_back();
                id.push_back(stk.back());
            }
            first[u] = static_cast<int>(id.size());
            id.push_back(u);
            stk.push_back(u);
        }
        while (stk.size() > 1) {
            stk.pop_back();
            id.push_back(stk.back());
        }
    }
};
