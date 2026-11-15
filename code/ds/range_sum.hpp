#pragma once

#include "../types.hpp"

struct RangeTag {
    bool hasSet = false;
    ll set = 0, add = 0;

    bool isEmpty() const {
        return !hasSet && add == 0;
    }

    // Appends a newer operation to the existing tag.
    void apply(const RangeTag& v) {
        if (v.hasSet) *this = v;
        else add += v.add;
    }
};

struct SumInfo {
    ll sum = 0;

    void apply(const RangeTag& v, int len) {
        if (v.hasSet) sum = v.set * len;
        sum += v.add * len;
    }

    friend SumInfo operator+(const SumInfo& a, const SumInfo& b) {
        return {a.sum + b.sum};
    }
};
