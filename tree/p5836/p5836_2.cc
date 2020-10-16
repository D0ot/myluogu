#include <bits/stdc++.h>

const int MAX = 10E5 + 1;

int fa[MAX];
std::string str;
std::string ans;

int find(int x) {
    if(x == fa[x]) {
        return x;
    } else {
        fa[x] = find(fa[x]);
        return fa[x];
    }
}

void merge(int x, int y) {
    fa[find(y)] = find(x);
}

int main(void) {
    int n,m;
    ans = "";
    std::cin >> n >> m;
    std::cin >> str;
    for(int i = 1; i <= n; ++i) {
        fa[i] = i;
    }

    int k, t;
    char c;
    for(int i = 0;i < n - 1; ++i) {
        std::cin >> k >> t;
        if(str[k-1] == str[t-1]) {
            merge(k, t);
        }
    }

    for(int i = 0;i < m; ++i) {
        std::cin >> k >> t >> c;
        if(find(k) == find(t) && str[k-1] != c) {
            ans.push_back('0');
        } else {
            ans.push_back('1');
        }
    }
    std::cout << ans;
    return 0;
}
