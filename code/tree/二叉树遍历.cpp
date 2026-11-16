#include <utility>
#include <vector>

// In solve: root, lc[] and rc[]; index 0 denotes a missing node.

std::vector<int> pre, in, post;
std::vector<std::pair<int, int>> stk;
if (root) stk.push_back({root, 0});
while (!stk.empty()) {
    auto [u, stage] = stk.back();
    stk.pop_back();
    if (stage == 0) {
        pre.push_back(u);
        stk.push_back({u, 1});
        if (lc[u]) stk.push_back({lc[u], 0});
    } else if (stage == 1) {
        in.push_back(u);
        stk.push_back({u, 2});
        if (rc[u]) stk.push_back({rc[u], 0});
    } else {
        post.push_back(u);
    }
}
