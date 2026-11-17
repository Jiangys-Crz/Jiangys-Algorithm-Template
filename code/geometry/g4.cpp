// https://www.luogu.com.cn/problem/P4724 - 三维凸包表面积
#include <bits/stdc++.h>

using u32 = unsigned;
using ll = long long;
using u64 = unsigned long long;
using i128 = __int128;

constexpr double eps = 1e-10;
constexpr int N = 4010;

int n, m;
bool g[N][N];

double rand_eps() {
	return ((double)rand() / RAND_MAX - 0.5) * eps;
}

struct Point {
	double x, y, z;
	Point(double x_ = 0, double y_ = 0, double z_ = 0) : x(x_), y(y_), z(z_) {}

    Point &operator+=(Point p) & {
        x += p.x;
        y += p.y;
        z += p.z;
        return *this;
    }
    Point &operator-=(Point p) & {
        x -= p.x;
        y -= p.y;
        z -= p.z;
        return *this;
    }
    Point &operator*=(double v) & {
        x *= v;
        y *= v;
        z *= v;
        return *this;
    }
    Point operator-() const {
        return Point(-x, -y, -z);
    }
    friend Point operator+(Point a, Point b) {
        return a += b;
    }
    friend Point operator-(Point a, Point b) {
        return a -= b;
    }
    friend Point operator*(Point a, double b) {
        return a *= b;
    }
    friend Point operator*(double a, Point b) {
        return b *= a;
    }
    friend Point operator/(Point a, double b) {
    	return {a.x / b, a.y / b, a.z / b};
    }
    friend bool operator==(Point a, Point b) {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }
    friend std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y >> p.z;
    }
    friend std::ostream &operator<<(std::ostream &os, Point p) {
        return os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    }
	// 随机扰动
	void shake() {
		x += rand_eps(), y += rand_eps(), z += rand_eps();
	}

} q[N];

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point cross(Point a, Point b) {
    return {a.y * b.z - b.y * a.z, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

double square(Point p) {
    return dot(p, p);
}

double length(Point p) {
    return std::sqrt(double(square(p)));
}

// 面
struct Plane {
	int v[3];
	Point norw() {
		return cross(q[v[1]] - q[v[0]], q[v[2]] - q[v[0]]);
	}
	double area() {
		return length(norw()) / 2;
	}
	bool above(Point a) {
		return dot((a - q[v[0]]), norw()) >= 0;
	}
} plane[N], np[N];

void getConvex3d() {
	plane[m ++] = {0, 1, 2};
	plane[m ++] = {2, 1, 0};
	for (int i = 3; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < m; j++) {
			bool t = plane[j].above(q[i]);
			if (!t) np[cnt++] = plane[j];
			for (int k = 0; k < 3; k++) {
				g[plane[j].v[k]][plane[j].v[(k + 1) % 3]] = t;
			}
		}
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < 3; k++) {
				int a = plane[j].v[k], b = plane[j].v[(k + 1) % 3];
				if (g[a][b] && !g[b][a]) {
					np[cnt++] = {a, b, i};
				}
			}
		}
		m = cnt;
		for (int j = 0; j < m; j++) {
			plane[j] = np[j];
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << std::fixed << std::setprecision(6);

	std::cin >> n;
	for (int i = 0; i < n; i++) {
		std::cin >> q[i];
		q[i].shake();
	}

	getConvex3d();

	double ans = 0;

	for (int i = 0; i < m; i++) {
		ans += plane[i].area();
	}
	std::cout << ans << '\n';

	return 0;
}