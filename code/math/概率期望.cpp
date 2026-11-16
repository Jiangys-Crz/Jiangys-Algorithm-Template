// In solve: p contains success probabilities of independent events.
// n is the number of equally likely types in the coupon collector model.
long double atLeastOne = 0;
for (long double x : p) atLeastOne += (1 - atLeastOne) * x;

long double expected = 0;
for (int missing = n; missing >= 1; --missing) {
    expected += static_cast<long double>(n) / missing;
}
