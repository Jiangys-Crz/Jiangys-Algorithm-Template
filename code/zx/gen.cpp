#include <charconv>
#include <iostream>
#include <random>
#include <string_view>

using namespace std;

using uint = unsigned int;
using ll = long long;

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "usage: gen SEED\n";
        return 2;
    }
    string_view arg = argv[1];
    uint seed;
    auto end = arg.data() + arg.size();
    auto [ptr, ec] = from_chars(arg.data(), end, seed);
    if (ec != errc{} || ptr != end) {
        cerr << "invalid uint seed\n";
        return 2;
    }

    mt19937 rng(seed);
    int n = static_cast<int>(uniform_int_distribution<ll>(1, 20)(rng));
    uniform_int_distribution<ll> pick(-10, 10);
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        cout << pick(rng) << (i + 1 == n ? '\n' : ' ');
    }
}
