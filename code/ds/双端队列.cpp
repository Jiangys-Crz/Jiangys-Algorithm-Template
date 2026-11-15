#include <deque>
#include <utility>
#include <vector>

std::vector<int> arrangeDeque(const std::vector<std::pair<bool, int>>& ops) {
    std::deque<int> q;
    for (auto [left, x] : ops) {
        if (left) q.push_front(x);
        else q.push_back(x);
    }
    return {q.begin(), q.end()};
}
