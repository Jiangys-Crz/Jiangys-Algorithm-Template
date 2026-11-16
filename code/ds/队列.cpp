#include <queue>

// In solve: int n >= 1. Discard the first card, then rotate the next.

std::queue<int> q;
for (int i = 1; i <= n; ++i) q.push(i);
while (q.size() > 1) {
    q.pop();
    int x = q.front();
    q.pop();
    q.push(x);
}
int last = q.front();
