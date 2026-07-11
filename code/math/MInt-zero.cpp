template<class T>
constexpr T power(T a, u64 b, T res = 1) {
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

template<u32 P>
constexpr u32 mulMod(u32 a, u32 b) {
    return u64(a) * b % P;
}

template<u64 P>
constexpr u64 mulMod(u64 a, u64 b) {
    u64 res = a * b - u64(1.L * a * b / P - 0.5L) * P;
    res %= P;
    return res;
}

template<typename U, U P>
constexpr U rawPower(U base, u64 exp) {
    U res = 1;
    base %= P;
    while (exp > 0) {
        if (exp % 2 == 1) {
            if constexpr (sizeof(U) == 4) res = mulMod<u32(P)>(res, base);
            else res = mulMod<u64(P)>(res, base);
        }
        
        if constexpr (sizeof(U) == 4) base = mulMod<u32(P)>(base, base);
        else base = mulMod<u64(P)>(base, base);
        
        exp /= 2;
    }
    return res;
}

template<std::unsigned_integral U, U P>
struct ModIntBase {
public:
    constexpr ModIntBase() : x(1), zeros(1) {}
    template<typename T>
    constexpr ModIntBase(T x_) {
        using S = std::make_signed_t<U>;
        S v = x_ % S(P);
        if (v < 0) v += P;
        
        if (v == 0) {
            x = 1;
            zeros = 1;
        } else {
            x = U(v);
            zeros = 0;
        }
    }
    
    constexpr static U mod() { return P; }
    
    constexpr U val() const {
        return zeros > 0 ? 0 : x;
    }

    constexpr U raw_x() const { return x; }
    
    constexpr ModIntBase operator-() const {
        if (zeros > 0) return *this;
        return ModIntBase(P - x);
    }
    
    constexpr ModIntBase inv() const {
        ModIntBase res;
        res.x = rawPower<U, P>(x, P - 2);
        res.zeros = -zeros;
        return res;
    }
    
    constexpr ModIntBase &operator*=(const ModIntBase &rhs) & {
        x = mulMod<P>(x, rhs.x);
        zeros += rhs.zeros;
        return *this;
    }
    
    constexpr ModIntBase &operator/=(const ModIntBase &rhs) & {
        x = mulMod<P>(x, rawPower<U, P>(rhs.x, P - 2));
        zeros -= rhs.zeros;
        return *this;
    }

    constexpr ModIntBase &operator+=(const ModIntBase &rhs) & {
        U v1 = val();
        U v2 = rhs.val();
        U res = v1 + v2;
        if (res >= P) res -= P;
        *this = ModIntBase(res);
        return *this;
    }
    
    constexpr ModIntBase &operator-=(const ModIntBase &rhs) & {
        U v1 = val();
        U v2 = rhs.val();
        U res = (v1 < v2) ? (v1 + P - v2) : (v1 - v2);
        *this = ModIntBase(res);
        return *this;
    }
    
    friend constexpr ModIntBase operator*(ModIntBase lhs, const ModIntBase &rhs) { lhs *= rhs; return lhs; }
    friend constexpr ModIntBase operator/(ModIntBase lhs, const ModIntBase &rhs) { lhs /= rhs; return lhs; }
    friend constexpr ModIntBase operator+(ModIntBase lhs, const ModIntBase &rhs) { lhs += rhs; return lhs; }
    friend constexpr ModIntBase operator-(ModIntBase lhs, const ModIntBase &rhs) { lhs -= rhs; return lhs; }
    friend constexpr std::istream &operator>>(std::istream &is, ModIntBase &a) {
        i64 i;
        is >> i;
        a = i;
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const ModIntBase &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(const ModIntBase &lhs, const ModIntBase &rhs) {
        return lhs.val() == rhs.val();
    }
    
private:
    U x;
    int zeros;
};

template<u32 P>
using ModInt = ModIntBase<u32, P>;
template<u64 P>
using ModInt64 = ModIntBase<u64, P>;

constexpr int mod1 = 1000000007, mod2 = 998244353;
using Z = ModInt<mod1>;