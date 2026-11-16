#include <iostream>
#include <utility>
#include <vector>

int main() {
    int n, root;
    if (!(std::cin >> n >> root)) return 0;
    std::vector<int> lc(n + 1), rc(n + 1), pre, in, post;
    for (int u = 1; u <= n; ++u) std::cin >> lc[u] >> rc[u];

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
    for (const auto* order : {&pre, &in, &post}) {
        for (int u : *order) std::cout << u << ' ';
        std::cout << '\n';
    }
}
