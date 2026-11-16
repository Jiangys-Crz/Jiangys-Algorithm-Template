#include <algorithm>
#include <tuple>
#include <vector>

using ll = long long;

struct Record {
    int id;
    ll score, penalty;
};

// In solve: vector<Record> a. Sort descending score, then ascending penalty and id.

std::sort(a.begin(), a.end(), [](const Record& x, const Record& y) {
    if (x.score != y.score) return x.score > y.score;
    return std::tie(x.penalty, x.id) < std::tie(y.penalty, y.id);
});
