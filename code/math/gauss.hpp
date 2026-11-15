#pragma once

#include <algorithm>
#include <bitset>
#include <cmath>
#include <utility>
#include <vector>

enum class LinearStatus { unique, infinite, inconsistent };

template<class Solution>
struct LinearResult {
    LinearStatus status;
    int rank;
    Solution x{};
};

inline LinearResult<std::vector<long double>> gauss(
    std::vector<std::vector<long double>> a, int m, long double eps = 1e-12L) {
    int n = static_cast<int>(a.size()), row = 0;
    std::vector<int> where(m, -1);
    for (int col = 0; col < m && row < n; ++col) {
        int p = row;
        for (int i = row + 1; i < n; ++i) {
            if (std::abs(a[i][col]) > std::abs(a[p][col])) p = i;
        }
        if (std::abs(a[p][col]) <= eps) continue;

        std::swap(a[p], a[row]);
        where[col] = row;
        long double d = a[row][col];
        for (int j = col; j <= m; ++j) a[row][j] /= d;
        for (int i = 0; i < n; ++i) {
            if (i == row) continue;
            long double k = a[i][col];
            for (int j = col + 1; j <= m; ++j) a[i][j] -= k * a[row][j];
            a[i][col] = 0;
        }
        ++row;
    }
    for (int i = row; i < n; ++i) {
        if (std::abs(a[i][m]) > eps) return {LinearStatus::inconsistent, row};
    }
    std::vector<long double> x(m);
    for (int j = 0; j < m; ++j) {
        if (where[j] != -1) x[j] = a[where[j]][m];
    }
    auto status = row == m ? LinearStatus::unique : LinearStatus::infinite;
    return {status, row, std::move(x)};
}

template<std::size_t M>
LinearResult<std::bitset<M>> xorGauss(std::vector<std::bitset<M + 1>> a) {
    int n = static_cast<int>(a.size()), row = 0;
    std::vector<int> where(M, -1);
    for (std::size_t col = 0; col < M && row < n; ++col) {
        int p = row;
        while (p < n && !a[p][col]) ++p;
        if (p == n) continue;

        std::swap(a[p], a[row]);
        where[col] = row;
        for (int i = 0; i < n; ++i) {
            if (i != row && a[i][col]) a[i] ^= a[row];
        }
        ++row;
    }
    for (int i = row; i < n; ++i) {
        if (a[i][M]) return {LinearStatus::inconsistent, row};
    }
    std::bitset<M> x;
    for (std::size_t j = 0; j < M; ++j) {
        if (where[j] != -1) x[j] = a[where[j]][M];
    }
    auto status = static_cast<std::size_t>(row) == M
                      ? LinearStatus::unique : LinearStatus::infinite;
    return {status, row, x};
}
