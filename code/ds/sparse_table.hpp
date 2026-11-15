#pragma once

#include <utility>
#include <vector>

template<class T, class Op>
struct SparseTable {
    Op op;
    std::vector<int> lg;
    std::vector<std::vector<T>> st;

    SparseTable(const std::vector<T>& a, Op op)
        : op(std::move(op)), lg(a.size()), st{a} {
        int n = static_cast<int>(a.size()) - 1;
        for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;
        for (int j = 1; j <= lg[n]; ++j) {
            int len = 1 << j, half = len / 2;
            const auto& prev = st.back();
            std::vector<T> row(a.size());
            for (int i = 1; i <= n - len + 1; ++i) {
                row[i] = this->op(prev[i], prev[i + half]);
            }
            st.push_back(std::move(row));
        }
    }

    T query(int l, int r) const {
        int j = lg[r - l + 1];
        return op(st[j][l], st[j][r - (1 << j) + 1]);
    }
};
