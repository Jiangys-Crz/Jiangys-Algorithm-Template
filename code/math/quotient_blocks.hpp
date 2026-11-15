using ull = unsigned long long;

#ifndef XCPC_MATH_QUOTIENT_BLOCKS_HPP
#define XCPC_MATH_QUOTIENT_BLOCKS_HPP

template<class Visit>
void quotientBlocks(ull n, Visit visit) {
    for (ull l = 1; l <= n; ) {
        ull q = n / l, r = n / q;
        visit(l, r, q);
        if (r == n) break;
        l = r + 1;
    }
}

#endif
