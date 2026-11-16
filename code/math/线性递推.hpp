#include <cassert>
#include <utility>
#include <vector>

using ull = unsigned long long;

#ifndef XCPC_MATH_POWER_HPP
#define XCPC_MATH_POWER_HPP

template<class T>
constexpr T power(T a, ull b, T res = T{1}) {
    while (b) {
        if (b & 1) res = res * a;
        b >>= 1;
        if (b) a = a * a;
    }
    return res;
}

#endif

#ifndef XCPC_MATH_MATRIX_HPP
#define XCPC_MATH_MATRIX_HPP

template<class T>
struct Matrix {
    int n, m;
    vector<vector<T>> a;

    Matrix(int n, int m) : n(n), m(m), a(n, vector<T>(m)) {}

    vector<T>& operator[](int i) { return a[i]; }
    const vector<T>& operator[](int i) const { return a[i]; }

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
    return power(move(a), k, move(id));
}

#endif

#ifndef XCPC_MATH_LINEAR_RECURRENCE_HPP
#define XCPC_MATH_LINEAR_RECURRENCE_HPP

template<class T>
T linearRecurrence(const vector<T>& initial,
                   const vector<T>& coeff, ull k) {
    int d = static_cast<int>(initial.size());
    if (k < initial.size()) return initial[k];

    Matrix<T> tr(d, d);
    for (int i = 0; i < d; ++i) tr[0][i] = coeff[i];
    for (int i = 1; i < d; ++i) tr[i][i - 1] = T{1};
    auto p = matrixPower(move(tr), k - (d - 1));
    T ans{};
    for (int i = 0; i < d; ++i) ans = ans + p[0][i] * initial[d - 1 - i];
    return ans;
}

#endif
