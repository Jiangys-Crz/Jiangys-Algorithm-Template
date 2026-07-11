std::mt19937_64 rng(std::chrono::system_clock::now().time_since_epoch().count());

// 随机生成 [l, r) 范围的数据
i64 rd(i64 l, i64 r) {
	return (rng() % r) + l;
}