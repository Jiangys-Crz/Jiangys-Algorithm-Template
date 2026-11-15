#include <utility>
#include <vector>

struct BinaryTraversal {
    std::vector<int> pre, in, post;
};

BinaryTraversal traverseBinary(const std::vector<int>& lc,
                               const std::vector<int>& rc, int root) {
    BinaryTraversal res;
    if (!root) return res;

    std::vector<std::pair<int, int>> stk{{root, 0}};
    while (!stk.empty()) {
        auto [u, stage] = stk.back();
        stk.pop_back();
        if (stage == 0) {
            res.pre.push_back(u);
            stk.push_back({u, 1});
            if (lc[u]) stk.push_back({lc[u], 0});
        } else if (stage == 1) {
            res.in.push_back(u);
            stk.push_back({u, 2});
            if (rc[u]) stk.push_back({rc[u], 0});
        } else {
            res.post.push_back(u);
        }
    }
    return res;
}
