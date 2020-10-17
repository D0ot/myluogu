#include <bits/stdc++.h>

const int MAX = 1E3 + 10;

struct Edge {
    int u,v,w;
};

int a,b,fa[MAX];
// TODO 
// ERROR VERSION : Edge edge[MAX];
// Runtime Error
Edge edge[MAX * MAX];

int find(int x) {
    if(x == fa[x]) {
        return x;
    }else {
        return fa[x] = find(fa[x]);
    }
}

void merge(int x, int y) {
    fa[find(x)] = find(y);
}

bool cmp(Edge &a, Edge &b) {
    return a.w < b.w;
}

int main(void) {
    std::cout.sync_with_stdio(false);
    std::cin.sync_with_stdio(false);
    std::cin >> a >> b;

    for(int i = 1; i <= b; ++i) {
        fa[i] = i;
    }

    int w;
    int cnt = 0;
    for(int i = 1; i <= b; ++i) {
        for(int j = 1; j <= b; ++j) {
            std::cin >> w;
            if(i < j && w) {
                edge[++cnt].u = i;
                edge[cnt].v = j;
                edge[cnt].w = w;
            }
        }
    }

    std::sort(edge + 1, edge + cnt + 1, cmp);

    int cost = 0;
    int bc = 0;
    for(int i = 1; i <= cnt; ++i) {
        if(find(edge[i].u) != find(edge[i].v)) {
            cost += std::min(a, edge[i].w);
            merge(edge[i].u, edge[i].v);
            ++bc;
        }
    }

    if(bc < b) {
        cost += (b - bc) * a;
    }
    std::cout << cost;
    return 0;
}