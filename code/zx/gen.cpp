#include <charconv>
#include <iostream>
#include <string_view>

#include "random_cases.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: gen SEED\n";
        return 2;
    }
    std::string_view arg = argv[1];
    uint seed;
    auto end = arg.data() + arg.size();
    auto [ptr, ec] = std::from_chars(arg.data(), end, seed);
    if (ec != std::errc{} || ptr != end) {
        std::cerr << "invalid uint seed\n";
        return 2;
    }

    RandomEngine rng(seed);
    int n = static_cast<int>(rng.next(1, 20));
    auto a = randomArray(rng, n, -10, 10);
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        std::cout << a[i] << (i + 1 == n ? '\n' : ' ');
    }
}
