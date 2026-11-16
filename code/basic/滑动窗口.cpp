#include <algorithm>

// n 为序列长度。
// 待填写：初始化空窗口的状态。
auto add = [&](int i) {
    // 待填写：向窗口加入下标 i 对应的元素。
};
auto remove = [&](int i) {
    // 待填写：从窗口移除下标 i 对应的元素。
};
auto valid = [&]() -> bool {
    // 当前窗口可行时返回 true，否则返回 false。
    // 可行窗口的每个子区间也必须可行。
    return /* 待填写：判定当前窗口是否可行 */;
};

int l = 0, ans = 0;
for (int r = 0; r < n; ++r) {
    add(r);
    while (l <= r && !valid()) remove(l++);
    ans = max(ans, r - l + 1);
}
