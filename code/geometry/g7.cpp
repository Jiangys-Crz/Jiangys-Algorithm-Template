// 旋转卡壳，返回最远点对距离（多边形直径）
// id: 返回的凸包点的下标
// a: 排好序的原始点对
template<class T>
double RotatingCalipers(std::vector<int>& id, std::vector<Point<T>>& a) {
	int m = id.size() - 1;
	if (m <= 2) {
		return dis(a[0], a.back());
	}
	double ans = 0;
	for (int i = 0, j = 2; i < m; i++) {
		auto p1 = a[id[i]], p2 = a[id[(i + 1) % m]];
		while (cross(p1, p2, a[id[j]]) < cross(p1, p2, a[id[j + 1]])) {
			j = (j + 1) % m;
		}
		ans = std::max({ans, dis(p1, a[id[j]]), dis(p2, a[id[j]])});
	}

	return ans;
}