#include <bits/stdc++.h>

const int MAX = 1E5 + 10;

struct Edge {
    int u,v,w;
};

int n, m, k, fa[MAX];
Edge edge[MAX];

int find(int x) {
    if(x == fa[x]) {
        return x;
    } else {
        return fa[x] = find(fa[x]);
    }
}

void merge(int x, int y) {
    fa[find(x)] = find(y);
}

bool cmp(Edge &a, Edge &b) {
    return a.w > b.w;
}


int main(void) {
    std::cin >> n >> m >> k;

    for(int i = 1; i <= m; ++i) {
        std::cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }

    for(int i = 1; i <= n; ++i) {
        fa[i] = i;
    }

    std::sort(edge + 1, edge + m + 1, cmp);

    int cost = 0;
    int t = 0;
    for(int i = 1; i <= m && t != k ; ++i) {
        if(find(edge[i].u) != find(edge[i].v)) {
            // TODO
            // ERROR merge(edge[i].u, edge[i].w);
            merge(edge[i].u, edge[i].v);
            cost += edge[i].w;
            ++t;
        }
    }

    std::cout << cost;
    return 0;
}