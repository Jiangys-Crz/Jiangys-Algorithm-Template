// 返回构成凸包的点的下标，注意这里的点返回了两次 0 点
template<class T>
std::vector<int> getConvex(std::vector<Point<T>> &a) {
	int n = a.size();
	sort(a.begin(), a.end(),[&](auto p1, auto p2){
			if (p1.x == p2.x) {
				return p1.y < p2.y;
			}
			return p1.x < p2.x;
		});
	std::vector<bool> st(n, false);
	std::vector<int> stk;
	for (int i = 0; i < n; i++) {
		while (stk.size() >= 2 && cross(a[stk[stk.size() - 2]], a[stk.back()], a[i]) <= 0) {
			if (cross(a[stk[stk.size() - 2]], a[stk.back()], a[i]) < 0) {
				st[stk.back()] = false;
				stk.pop_back();
			} else {
				stk.pop_back();
			}
		}
		stk.push_back(i);
		st[i] = true;
	}
	st[0] = false;
	for (int i = n - 1; i >= 0; i--) {
		if (st[i]) continue;
		while (stk.size() >= 2 && cross(a[stk[stk.size() - 2]], a[stk.back()], a[i]) <= 0) {
			if (cross(a[stk[stk.size() - 2]], a[stk.back()], a[i]) < 0) {
				st[stk.back()] = false;
				stk.pop_back();
			} else {
				stk.pop_back();
			}
		}
		stk.push_back(i);
		st[i] = true;
	}
	return stk;
}