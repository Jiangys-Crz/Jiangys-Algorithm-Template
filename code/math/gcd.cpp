using ull = unsigned long long;

// In solve: ull a, b. The GCD is stored in a.

while (b) {
    ull r = a % b;
    a = b;
    b = r;
}
