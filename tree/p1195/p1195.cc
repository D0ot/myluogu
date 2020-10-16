#include <bits/stdc++.h>

const int MAXN = 1E3 + 10;
const int MAXM = 1E4 + 10;


int fa[MAXN];

int find(int x) {
    if(x == fa[x]) {
        return x;
    } else {
        fa[x] = find(fa[x]);
        return fa[x];
    }
}

void merge(int x, int y) {
    fa[find(x)] = find(y);
}

bool same(int x, int y) {
    return find(x) == find(y);
}

int u[MAXM], v[MAXM], w[MAXM];
int s[MAXM];
int n,m,k;

bool cmp(int a, int b) {
    return w[a] < w[b];
}

int kruskal() {
    int cost = 0;
    int diff = n - k;

    int i = 1;
    // s[i] is index
    while(diff && i <= m) {
        int j = s[i];
        if(find(u[j]) != find(v[j])) { 
            merge(u[j], v[j]);
            cost += w[j];
            diff--;
        }
        ++i;
    }
    return cost;
}

int main(void) {
    std::cin >> n >> m >> k;

    for(int i = 1; i < n; ++i) {
        fa[i] = i;
    }

    for(int i = 1; i <= m ; ++i) {
        std::cin >> u[i] >> v[i] >> w[i];
        s[i] = i;
    }

    if(k > n || n - m > k) {
        std::cout << "No Answer";
        return 0;
    } else if(k == n) {
        std::cout << 0;
        return 0;
    }

    std::sort(s + 1, s + 1 + m, cmp);

    #ifdef MYDEBUG
    for(int i = 1; i <= m; ++i) {
        std::cout << w[s[i]] << ' ';
    }
    std::cout << '\n';
    #endif

    std::cout << kruskal();
    return 0;
}

