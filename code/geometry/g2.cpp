double R; // 圆的半径
Point<double> r = {0, 0}; // 圆心坐标

template<class T>
bool pointOnSegment(Point<T> p, Point<T> a, Point<T> b) {
    return !sign(cross(p - a, p - b)) && sign(dot(p - a, p - b)) <= 0;
}

// 求扇形面积
template<class T>
double getSector(Point<T> a, Point<T> b) {
	auto angle = acos(dot(a, b) / length(a) / length(b));
	if (sign(cross(a, b)) < 0) angle = -angle;
	return R * R * angle / 2;
}

// 圆心到直线的距离和直线与圆的两个交点
template<class T>
std::tuple<T, Point<T>, Point<T>> getCircleLineIntersection(Point<T> a, Point<T> b) {
	auto e = lineIntersection(a, b - a, r, rotate(b - a, PI / 2));
	auto mind = dis(r, e);
	if (!pointOnSegment(e, a, b)) {
		mind = std::min(dis(r, a), dis(r, b));
	}
	if (dcmp(R, mind) <= 0) return {mind, {}, {}};
	auto len = std::sqrt(R * R - dis(r, e) * dis(r, e));
	auto pa = e + getUnitVector(a - b) * len;
	auto pb = e + getUnitVector(b - a) * len;
	return {mind, pa, pb};
}

// 三角形和圆的面积交
template<class T>
double getCircleTriangleArea(Point<T> a, Point<T> b) {
	auto da = dis(r, a), db = dis(r, b);
	if (dcmp(R, da) >= 0 && dcmp(R, db) >= 0) return cross(a, b) / 2;
	if (!sign(cross(a, b))) return 0;
	auto [mind, pa, pb] = getCircleLineIntersection(a, b);
	if (dcmp(R, mind) <= 0) return getSector(a, b);
	if (dcmp(R, da) >= 0) return cross(a, pb) / 2 + getSector(pb, b);
	if (dcmp(R, db) >= 0) return getSector(a, pa) + cross(pa, b) / 2;
	return getSector(a, pa) + cross(pa, pb) / 2 + getSector(pb, b);
}

// 返回多边形与圆的面积交
template<class T>
double work(std::vector<Point<T>>& q) {
	double ans = 0;
	int n = q.size();
	for (int i = 0; i < n; i++) {
		ans += getCircleTriangleArea(q[i], q[(i + 1) % n]);
	}
	return fabs(ans);
}