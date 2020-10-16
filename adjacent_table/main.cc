#include <bits/stdc++.h>

// reference
// https://www.cnblogs.com/ECJTUACM-873284962/p/6905416.html
// better version

const int MAX = 10E5 + 1;

// edges
int u[MAX], v[MAX], w[MAX], fst[MAX], nxt[MAX];

int main(void) {
    int n, m;
    std::cin >> n >> m;

    for(int i = 1; i <= n; ++i) {
        fst[i] = -1;
    }

    for(int i = 1; i <= m; ++i) {
        std::cin >> u[i] >> v[i] >> w[i];
        nxt[i] = fst[u[i]];
        fst[u[i]] = i;
    }



}

