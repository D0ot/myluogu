#include <bits/stdc++.h>

const int MAXN = 1E4 + 10;
const int MAXM = 2E4 + 10;

int u[MAXM], v[MAXM], w[MAXM];
int n,m,s,t;
int fa[MAXN];
int st[MAXM];
int ans;


int find(int x) {
    if(x == fa[x]) {
        return x;
    } else {
        return fa[x] = find(fa[x]);
    }
}

void merge(int x, int y) {
    fa[find(y)] = find(x);
    // fa[fy] = fx
}

int cmp(int a, int b) {
    return w[a] < w[b];
}

// TODO
// not fully understand
void kruskal() {
    int i = 1, j;
    while(i <= m) {
        j = st[i];
        if(find(u[j]) != find(v[j])) {
            merge(u[j], v[j]);
            if(find(s) == find(t)) {
                ans = w[j];
                break;
            }
        }
        ++i;
    }
}

void init() {
    std::cin >> n >> m >> s >> t;
    for(int i = 1; i <=m; ++i) {
        std::cin >> u[i] >> v[i] >> w[i];
        st[i] = i;
    }

    for(int i = 1; i <=n; ++i) {
        fa[i] = i;
    }
    
}

int main() {
    init();
    
    std::sort(st + 1, st + m + 1, cmp);
    kruskal();
    std::cout << ans;
}


