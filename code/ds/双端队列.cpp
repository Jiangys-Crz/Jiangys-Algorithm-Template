#include <iostream>
#include <deque>

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::deque<int> q;
    for (int i = 0; i < n; ++i) {
        int left, x;
        std::cin >> left >> x;
        if (left) q.push_front(x);
        else q.push_back(x);
    }
    for (int x : q) std::cout << x << ' ';
    std::cout << '\n';
}
