#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using ll = long long;

struct Record {
    int id;
    ll score, penalty;
};

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::vector<Record> a(n);
    for (auto& [id, score, penalty] : a) std::cin >> id >> score >> penalty;
    std::sort(a.begin(), a.end(), [](const Record& x, const Record& y) {
        if (x.score != y.score) return x.score > y.score;
        return std::tie(x.penalty, x.id) < std::tie(y.penalty, y.id);
    });
    for (const auto& row : a) std::cout << row.id << ' ';
    std::cout << '\n';
}
