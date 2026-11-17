// 下标从 0 开始。initial 是空子集状态。
// take(old, i) 根据旧状态计算选入第 i 项后的状态。
auto enumerate = [&](int l, int r) {
    vector<State> states{initial};
    for (int i = l; i < r; ++i) {
        size_t size = states.size();
        for (size_t j = 0; j < size; ++j) {
            State next = take(states[j], i);
            states.push_back(move(next));
        }
    }
    return states;
};

int mid = n / 2;
auto left = enumerate(0, mid);
auto right = enumerate(mid, n);

// 待填写：按组合条件为 right 建立查询结构。
for (const auto& x : left) {
    // 待填写：查询可与 x 配对的右侧状态，并更新答案。
}
