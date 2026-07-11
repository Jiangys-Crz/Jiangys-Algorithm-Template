// 最小矩形覆盖 传入凸包的下标和点，返回矩形的面积和四个顶点坐标
template<class T>
std::pair<double, std::vector<Point<T>>> MinimumRectangularCover(std::vector<int>& ids, std::vector<Point<T>>& q) {
	double area = INF;
	std::vector<Point<T>> ans(4);
	int n = ids.size() - 1;
	for (int i = 0, a = 2, b = 1, c = 2; i < n; i++) {
		auto d = q[ids[i]], e = q[ids[(i + 1) % n]];
		while (dcmp(cross(d, e, q[ids[a]]), cross(d, e, q[ids[(a + 1) % n]])) < 0) a = (a + 1) % n;
		while (dcmp(getProject(d, e, q[ids[b]]), getProject(d, e, q[ids[(b + 1) % n]])) < 0) b = (b + 1) % n;
		if (!i) c = a;
		while (dcmp(getProject(d, e, q[ids[c]]), getProject(d, e, q[ids[(c + 1) % n]])) > 0) c = (c + 1) % n;
		auto x = q[ids[a]], y = q[ids[b]], z = q[ids[c]];
		auto h = cross(d, e, x) / length(e - d);
		auto w = dot(y - z, e - d) / length(e - d);
		if (h * w < area) {
			area = h * w;
			ans[0] = d + getUnitVector(e - d) * getProject(d, e, y);
			ans[3] = d + getUnitVector(e - d) * getProject(d, e, z);
			auto u = getUnitVector(rotate(e - d, -PI / 2));
			ans[1] = ans[0] + u * h;
			ans[2] = ans[3] + u * h;
		}
	}
	return {area, ans};
}