#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::vector<int> a(n);
    for (int& x : a) std::cin >> x;
    std::sort(a.begin(), a.end());

    do {
        for (int x : a) std::cout << x << ' ';
        std::cout << '\n';
    } while (std::next_permutation(a.begin(), a.end()));
}
