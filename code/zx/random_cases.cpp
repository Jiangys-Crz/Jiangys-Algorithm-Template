using uint = unsigned int;
using ll = long long;

// 先设定种子 seed、规模 n 和闭区间 [l, r]，其中 n >= 1 且 l <= r。
// 同一测试用例的所有取样共用一个随机数引擎。
mt19937 rng(seed);

vector<ll> a(n);
uniform_int_distribution<ll> pick(l, r);
for (ll& x : a) x = pick(rng);

vector<int> id(n);
iota(id.begin(), id.end(), 1LL);
shuffle(id.begin(), id.end(), rng);

vector<pair<int, int>> edges;
for (int i = 1; i < n; ++i) {
    int p = uniform_int_distribution<int>(0, i - 1)(rng);
    edges.emplace_back(id[p], id[i]);
}
// 待填写：按题目的输入格式写出所需数据。
