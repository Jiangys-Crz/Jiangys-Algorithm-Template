#pragma once

#include <algorithm>

#include "point.hpp"

inline constexpr Real eps = 1e-12L;

template<class T>
constexpr int sgn(T x) {
    return (x > T{}) - (x < T{});
}

inline int sign(Real x, Real tol = eps) {
    return (x > tol) - (x < -tol);
}

inline int dcmp(Real a, Real b, Real absTol = eps, Real relTol = eps) {
    Real scale = std::max(std::abs(a), std::abs(b));
    return sign(a - b, std::max(absTol, relTol * scale));
}
