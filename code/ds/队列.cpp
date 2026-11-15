#include <queue>

int lastCard(int n) {
    std::queue<int> q;
    for (int i = 1; i <= n; ++i) q.push(i);
    while (q.size() > 1) {
        q.pop();
        int x = q.front();
        q.pop();
        q.push(x);
    }
    return q.front();
}
