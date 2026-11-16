using ull = unsigned long long;

// In solve: ull mask is the set to enumerate.

for (ull s = mask; ; s = (s - 1) & mask) {
    // TODO: Process the current submask s.
    if (s == 0) break;
}
