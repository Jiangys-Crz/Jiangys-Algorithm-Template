#include <charconv>
#include <iostream>
#include <random>
#include <string_view>

using uint = unsigned int;
using ll = long long;

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

    std::mt19937 rng(seed);
    int n = static_cast<int>(std::uniform_int_distribution<ll>(1, 20)(rng));
    std::uniform_int_distribution<ll> pick(-10, 10);
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        std::cout << pick(rng) << (i + 1 == n ? '\n' : ' ');
    }
}
