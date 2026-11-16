#include <algorithm>
#include <tuple>
#include <vector>

using ll = long long;

struct Record {
    int id;
    ll score, penalty;
};

// 先准备记录数组 a，按分数降序、罚时升序、编号升序排序。

sort(a.begin(), a.end(), [](const Record& x, const Record& y) {
    if (x.score != y.score) return x.score > y.score;
    return tie(x.penalty, x.id) < tie(y.penalty, y.id);
});
