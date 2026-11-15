#pragma once

#include <array>
#include <cassert>
#include <string_view>
#include <vector>

#include "alphabet.hpp"

template<class Alphabet = AlnumAlphabet>
class Trie {
public:
    void insert(std::string_view s) {
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

    bool erase(std::string_view s) {
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

    int query(std::string_view s) const {
        int u = walk(s);
        return u < 0 ? 0 : tr[u].cnt;
    }

    int prefixCount(std::string_view s) const {
        int u = walk(s);
        return u < 0 ? 0 : tr[u].pass;
    }

    void clear() {
        tr.assign(1, Node{});
    }

private:
    struct Node {
        std::array<int, Alphabet::size> ch{};
        int cnt = 0, pass = 0;
    };

    std::vector<Node> tr{Node{}};

    int walk(std::string_view s) const {
        int u = 0;
        for (unsigned char c : s) {
            int x = Alphabet::id(c);
            if (x < 0 || x >= Alphabet::size || !tr[u].ch[x]) return -1;
            u = tr[u].ch[x];
        }
        return u;
    }
};
