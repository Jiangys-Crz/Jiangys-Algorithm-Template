#include <cassert>
#include <utility>
#include <vector>

#ifndef XCPC_DS_SPARSE_TABLE_HPP
#define XCPC_DS_SPARSE_TABLE_HPP

template<class T, class Op>
struct SparseTable {
    Op op;
    vector<int> lg;
    vector<vector<T>> st;

    SparseTable(const vector<T>& a, Op op)
        : op(move(op)), lg(a.size()), st{a} {
        if (a.size() <= 1) return;
        int n = static_cast<int>(a.size()) - 1;
        for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;
        for (int j = 1; j <= lg[n]; ++j) {
            int len = 1 << j, half = len / 2;
            const auto& prev = st.back();
            vector<T> row(a.size());
            for (int i = 1; i <= n - len + 1; ++i) {
                row[i] = this->op(prev[i], prev[i + half]);
            }
            st.push_back(move(row));
        }
    }

    T query(int l, int r) const {
        assert(1 <= l && l <= r && r < static_cast<int>(lg.size()));
        int j = lg[r - l + 1];
        return op(st[j][l], st[j][r - (1 << j) + 1]);
    }
};

#endif
