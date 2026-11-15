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
