#include <vector>

#include "../types.hpp"

std::vector<int> previousSmaller(const std::vector<ll>& a) {
    int n = static_cast<int>(a.size());
    std::vector<int> ans(n, -1), stk;
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && a[stk.back()] >= a[i]) stk.pop_back();
        if (!stk.empty()) ans[i] = stk.back();
        stk.push_back(i);
    }
    return ans;
}
