#include <deque>

// In solve: ops is a list of (left, value); left selects the front.

std::deque<int> q;
for (auto [left, x] : ops) {
    if (left) q.push_front(x);
    else q.push_back(x);
}
