#include <ostream>

using ll = long long;

#ifndef XCPC_ZX_OPERATOR_OVERLOAD_HPP
#define XCPC_ZX_OPERATOR_OVERLOAD_HPP

struct Score {
    ll points = 0, penalty = 0;

    bool operator<(const Score& rhs) const {
        if (points != rhs.points) return points < rhs.points;
        return penalty > rhs.penalty;
    }

    bool operator>(const Score& rhs) const {
        return rhs < *this;
    }

    bool operator==(const Score& rhs) const {
        return points == rhs.points && penalty == rhs.penalty;
    }

    Score& operator+=(const Score& rhs) {
        points += rhs.points;
        penalty += rhs.penalty;
        return *this;
    }

    friend Score operator+(Score lhs, const Score& rhs) {
        return lhs += rhs;
    }

    friend ostream& operator<<(ostream& out, const Score& score) {
        return out << score.points << ' ' << score.penalty;
    }
};

#endif
