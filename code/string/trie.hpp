#include <array>
#include <cassert>
#include <string_view>
#include <vector>

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

#ifndef XCPC_STRING_TRIE_HPP
#define XCPC_STRING_TRIE_HPP

template<class Alphabet = AlnumAlphabet>
class Trie {
public:
    void insert(string_view s) {
        int u = 0;
        ++tr[u].pass;
        for (unsigned char c : s) {
            int x = Alphabet::id(c);
            assert(x >= 0 && x < Alphabet::size);
            if (!tr[u].ch[x]) {
                tr[u].ch[x] = static_cast<int>(tr.size());
                tr.emplace_back();
            }
            u = tr[u].ch[x];
            ++tr[u].pass;
        }
        ++tr[u].cnt;
    }

    bool erase(string_view s) {
        int end = walk(s);
        if (end < 0 || !tr[end].cnt) return false;
        --tr[end].cnt;
        int u = 0;
        --tr[u].pass;
        for (unsigned char c : s) {
            u = tr[u].ch[Alphabet::id(c)];
            --tr[u].pass;
        }
        return true;
    }

    int query(string_view s) const {
        int u = walk(s);
        return u < 0 ? 0 : tr[u].cnt;
    }

    int prefixCount(string_view s) const {
        int u = walk(s);
        return u < 0 ? 0 : tr[u].pass;
    }

    void clear() {
        tr.assign(1, Node{});
    }

private:
    struct Node {
        array<int, Alphabet::size> ch{};
        int cnt = 0, pass = 0;
    };

    vector<Node> tr{Node{}};

    int walk(string_view s) const {
        int u = 0;
        for (unsigned char c : s) {
            int x = Alphabet::id(c);
            if (x < 0 || x >= Alphabet::size || !tr[u].ch[x]) return -1;
            u = tr[u].ch[x];
        }
        return u;
    }
};

#endif
