constexpr int N = 3e6 + 10;

struct Trie {
    std::map<char, int> mp;
    int idx;
    std::vector<std::vector<int>> ch;
    std::vector<int> cnt;

    Trie(int n) {
    	ch.resize(n, std::vector<int>(63));
    	cnt.resize(n);
    	idx = 0;
    	ll id = 0;
        for (char c = 'a'; c <= 'z'; c++) mp[c] = ++id;
        for (char c = 'A'; c <= 'Z'; c++) mp[c] = ++id;
        for (char c = '0'; c <= '9'; c++) mp[c] = ++id;
    }

    void insert(std::string &s) {
        int u = 0;
        for (int i = 0; i < s.size(); i++) {
            int v = mp[s[i]];
            if (!ch[u][v]) ch[u][v] = ++idx;
            u = ch[u][v];
        }
        cnt[u]++;
    }
    void del(std::string &s) {
        int u = 0 ;
        for(int i = 0; i < s.size(); i++) {
            int v = mp[s[i]];
            u = ch[u][v];
        }
        cnt[u]--;
    }
    ll query(std::string &s) {
        int u = 0;
        for (int i = 0; i < s.size(); i++) {
            int v = mp[s[i]];
            if (!ch[u][v]) return 0;
            u = ch[u][v];
        }
        return cnt[u];
    }
    void clear() {
        for (int i = 0; i <= idx; i++) {
            cnt[i] = 0;
            for (int j = 0; j <= 62; j++) {
                ch[i][j] = 0;
            }
        }
        idx = 0;
    }
};