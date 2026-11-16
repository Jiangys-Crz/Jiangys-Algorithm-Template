#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using uint = unsigned int;

int main() {
    uint seed;
    if (!(std::cin >> seed)) return 0;
    std::mt19937 rng(seed);

    std::uniform_int_distribution<int> pick(1, 10);
    std::cout << pick(rng) << '\n';

    std::vector<int> a{1, 2, 3, 4, 5};
    std::shuffle(a.begin(), a.end(), rng);
    for (int x : a) std::cout << x << ' ';
    std::cout << '\n';
}
