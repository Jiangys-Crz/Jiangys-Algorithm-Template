#include <array>
#include <cassert>
#include <string_view>
#include <vector>

using ll = long long;

#ifndef XCPC_STRING_ALPHABET_HPP
#define XCPC_STRING_ALPHABET_HPP

struct LowercaseAlphabet {
    static constexpr int size = 26;

    static int id(unsigned char c) {
        if ('a' <= c && c <= 'z') return c - 'a';
        return -1;
    }
};

struct AlnumAlphabet {
    static constexpr int size = 62;

    static int id(unsigned char c) {
        if ('a' <= c && c <= 'z') return c - 'a';
        if ('A' <= c && c <= 'Z') return c - 'A' + 26;
        if ('0' <= c && c <= '9') return c - '0' + 52;
        return -1;
    }
};

#endif

#ifndef XCPC_STRING_AC_AUTOMATON_HPP
#define XCPC_STRING_AC_AUTOMATON_HPP

template<class Alphabet = LowercaseAlphabet>
class ACAutomaton {
public:
    int insert(std::string_view s) {
        assert(!built);
        int u = 0;
        for (unsigned char c : s) {
            int x = digit(c);
            if (!tr[u].ch[x]) {
                tr[u].ch[x] = static_cast<int>(tr.size());
                tr.emplace_back();
            }
            u = tr[u].ch[x];
        }
        return u;
    }

    void build() {
        if (built) return;
        for (int v : tr[0].ch) {
            if (v) order.push_back(v);
        }
        for (std::size_t i = 0; i < order.size(); ++i) {
            int u = order[i], p = tr[u].fail;
            for (int x = 0; x < Alphabet::size; ++x) {
                int& v = tr[u].ch[x];
                if (!v) {
                    v = tr[p].ch[x];
                } else {
                    tr[v].fail = tr[p].ch[x];
                    order.push_back(v);
                }
            }
        }
        built = true;
    }

    std::vector<ll> query(std::string_view s) const {
        assert(built);
        std::vector<ll> cnt(tr.size());
        int u = 0;
        cnt[0] = 1;
        for (unsigned char c : s) {
            u = tr[u].ch[digit(c)];
            ++cnt[u];
        }
        for (auto it = order.rbegin(); it != order.rend(); ++it) {
            int v = *it;
            cnt[tr[v].fail] += cnt[v];
        }
        return cnt;
    }

private:
    struct Node {
        std::array<int, Alphabet::size> ch{};
        int fail = 0;
    };

    bool built = false;
    std::vector<Node> tr{Node{}};
    std::vector<int> order;

    static int digit(unsigned char c) {
        int x = Alphabet::id(c);
        assert(x >= 0 && x < Alphabet::size);
        return x;
    }
};

#endif
