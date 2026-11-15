#pragma once

#include "matrix.hpp"

template<class T>
T linearRecurrence(const std::vector<T>& initial,
                   const std::vector<T>& coeff, ull k) {
    int d = static_cast<int>(initial.size());
    if (k < initial.size()) return initial[k];

    Matrix<T> tr(d, d);
    for (int i = 0; i < d; ++i) tr[0][i] = coeff[i];
    for (int i = 1; i < d; ++i) tr[i][i - 1] = T{1};
    auto p = matrixPower(std::move(tr), k - (d - 1));
    T ans{};
    for (int i = 0; i < d; ++i) ans = ans + p[0][i] * initial[d - 1 - i];
    return ans;
}
