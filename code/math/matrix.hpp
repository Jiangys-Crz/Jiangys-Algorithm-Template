#pragma once

#include <cassert>
#include <utility>
#include <vector>

#include "power.hpp"

template<class T>
struct Matrix {
    int n, m;
    std::vector<std::vector<T>> a;

    Matrix(int n, int m) : n(n), m(m), a(n, std::vector<T>(m)) {}

    std::vector<T>& operator[](int i) { return a[i]; }
    const std::vector<T>& operator[](int i) const { return a[i]; }

    static Matrix getIdentity(int n) {
        Matrix res(n, n);
        for (int i = 0; i < n; ++i) res[i][i] = T{1};
        return res;
    }

    friend Matrix operator*(const Matrix& a, const Matrix& b) {
        assert(a.m == b.n);
        Matrix res(a.n, b.m);
        for (int i = 0; i < a.n; ++i) {
            for (int k = 0; k < a.m; ++k) {
                for (int j = 0; j < b.m; ++j) {
                    res[i][j] = res[i][j] + a[i][k] * b[k][j];
                }
            }
        }
        return res;
    }
};

template<class T>
Matrix<T> matrixPower(Matrix<T> a, ull k) {
    assert(a.n == a.m);
    auto id = Matrix<T>::getIdentity(a.n);
    return power(std::move(a), k, std::move(id));
}
