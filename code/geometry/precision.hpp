#include <algorithm>
#include <cmath>

using Real = long double;

#ifndef XCPC_GEOMETRY_PRECISION_HPP
#define XCPC_GEOMETRY_PRECISION_HPP

inline constexpr Real eps = 1e-12L;

template<class T>
constexpr int sgn(T x) {
    return (x > T{}) - (x < T{});
}

inline int sign(Real x, Real tol = eps) {
    return (x > tol) - (x < -tol);
}

inline int dcmp(Real a, Real b, Real absTol = eps, Real relTol = eps) {
    Real scale = max(abs(a), abs(b));
    return sign(a - b, max(absTol, relTol * scale));
}

#endif
