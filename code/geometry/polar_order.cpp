#include <algorithm>

using ll = long long;

// 先准备点集 points 和极点 o，点类型采用 Point<ll>。
auto half = [](Point<ll> p) {
    return p.y > 0 || (p.y == 0 && p.x > 0) ? 0 : 1;
};
sort(points.begin(), points.end(), [&](Point<ll> a, Point<ll> b) {
    a = a - o;
    b = b - o;
    bool za = a == Point<ll>{}, zb = b == Point<ll>{};
    if (za || zb) return za && !zb;
    int ha = half(a), hb = half(b);
    if (ha != hb) return ha < hb;
    ll c = cross(a, b);
    if (c != 0) return c > 0;
    return square(a) < square(b);
});
