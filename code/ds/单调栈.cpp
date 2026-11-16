using ll = long long;

// a 为长度为 n 的数组。
// prev[i] 为 i 左侧最近的严格更小元素的下标。

vector<int> stk, prev(n, -1);
for (int i = 0; i < n; ++i) {
    while (!stk.empty() && a[stk.back()] >= a[i]) stk.pop_back();
    if (!stk.empty()) prev[i] = stk.back();
    stk.push_back(i);
}
