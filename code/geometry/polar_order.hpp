#pragma once

#include "point.hpp"

template<class T>
struct PolarLess {
    bool operator()(Point<T> a, Point<T> b) const {
        bool za = a == Point<T>{}, zb = b == Point<T>{};
        if (za || zb) return za && !zb;
        if (half(a) != half(b)) return half(a) < half(b);

        T c = cross(a, b);
        if (c != T{}) return c > T{};
        return square(a) < square(b);
    }

private:
    static int half(Point<T> p) {
        return p.y > T{} || (p.y == T{} && p.x > T{}) ? 0 : 1;
    }
};
