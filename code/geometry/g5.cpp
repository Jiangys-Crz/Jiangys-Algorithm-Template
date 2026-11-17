constexpr double PI = acos(-1);
constexpr double eps = 1e-12;

template<class T>
struct Point {
    T x;
    T y;
    Point(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}
    
    template<class U>
    operator Point<U>() {
        return Point<U>(U(x), U(y));
    }
    Point &operator+=(Point p) & {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point &operator-=(Point p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point &operator*=(T v) & {
        x *= v;
        y *= v;
        return *this;
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    friend Point operator+(Point a, Point b) {
        return a += b;
    }
    friend Point operator-(Point a, Point b) {
        return a -= b;
    }
    friend Point operator*(Point a, T b) {
        return a *= b;
    }
    friend Point operator*(T a, Point b) {
        return b *= a;
    }
    friend Point operator/(Point a, T b) {
    	return {a.x / b, a.y / b};
    }
    friend bool operator==(Point a, Point b) {
        return a.x == b.x && a.y == b.y;
    }
    friend std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    friend std::ostream &operator<<(std::ostream &os, Point p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

template<class T>
int sign(T x)
{
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}

template<class T>
int dcmp(T x, T y)
{
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}

template<class T>
T dot(Point<T> a, Point<T> b) {
    return a.x * b.x + a.y * b.y;
}

template<class T>
T cross(Point<T> a, Point<T> b) {
    return a.x * b.y - a.y * b.x;
}

template<class T>
T cross(Point<T> a, Point<T> b, Point<T> c) {
    return cross(b - a, c - a); // 可以判断ab和c的位置关系
}

template<class T>
double dis(Point<T> a, Point<T> b) {
	return std::sqrt(double((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

template<class T>
T square(Point<T> p) {
    return dot(p, p);
}

template<class T>
double length(Point<T> p) {
    return std::sqrt(double(square(p)));
}

long double length(Point<long double> p) {
    return std::sqrt(square(p));
}

template<class T>
struct Line {
    Point<T> a;
    Point<T> b;
    Line(Point<T> a_ = Point<T>(), Point<T> b_ = Point<T>()) : a(a_), b(b_) {}
};

// 顺时针旋转b(弧度制)角度
template<class T>
Point<T> rotate(Point<T> a, double b) {
    return {a.x * cos(b) + a.y * sin(b), -a.x * sin(b) + a.y * cos(b)};
}

// 两直线相交的交点
template<class T>
Point<T> lineIntersection(Line<T> l1, Line<T> l2) { // a+u*t
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}

// 两直线相交的交点
template<class T>
Point<T> lineIntersection(Point<T> p, Point<T> v, Point<T> q, Point<T> w) { // a+u*t
    return p + v * (cross(w, (p - q)) / cross(v, w));
}

// 获取线段的中垂线
template<class T>
Line<T> getVerticalLine(Point<T> a, Point<T> b) {
	return {(a + b) / 2, rotate(b - a, PI / 2)};
}

template<class T>
struct Circle
{
    Point<T> p; // 圆心
    T r; // 半径
};

// 三点确定一个圆
template<class T>
Circle<T> getCircle(Point<T> a, Point<T> b, Point<T> c) {
	auto u = getVerticalLine(a, b), v = getVerticalLine(a, c);
	auto p = lineIntersection(u.a, u.b, v.a, v.b);
	return {p, dis(p, a)};
}

// 最小圆覆盖
template<class T>
Circle<T> MinimumCircleCovering(std::vector<Point<T>>& q) {
	random_shuffle(q.begin(), q.end());
	int n = q.size();
	Circle<T> c({q[0], 0});
	for (int i = 0; i < n; i++) {
		if (dcmp(c.r, dis(c.p, q[i])) < 0) {
			c = {q[i], 0};
			for (int j = 0; j < i; j++) {
				if (dcmp(c.r, dis(c.p, q[j])) < 0) {
					c = {(q[i] + q[j]) / 2, dis(q[i], q[j]) / 2};
					for (int k = 0; k < j; k++) {
						if (dcmp(c.r, dis(c.p, q[k])) < 0) {
							c = getCircle(q[i], q[j], q[k]);
						}
					}
				}
			}
		}
	}
	return c;
}