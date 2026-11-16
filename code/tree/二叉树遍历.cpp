#include <utility>
#include <vector>

// 先准备根节点 root 以及左右子节点数组 lc 和 rc。编号 0 表示空节点。

vector<int> pre, in, post;
vector<pair<int, int>> stk;
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
