#include <iostream>
#include <queue>

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::queue<int> q;
    for (int i = 1; i <= n; ++i) q.push(i);
    while (q.size() > 1) {
        q.pop();
        int x = q.front();
        q.pop();
        q.push(x);
    }
    std::cout << q.front() << '\n';
}
