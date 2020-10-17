#include <bits/stdc++.h>



const int MAX = 1E3 + 10;

int n,m;
int x[MAX], y[MAX];


struct Edge {
    int x,y;
    double dis;
};

int fa[MAX];
Edge edge[MAX * MAX];

int find(int x) {
    if(x == fa[x]) {
        return x;
    } else {
        return fa[x] = find(fa[x]);
    }
}

double distance(int a, int b) {
    // TODO 
    // int * int 会超过int所以得先用double
    double x1, x2, y1, y2;
    x1 = x[a]; x2 = x[b]; y1 = y[a]; y2 = y[b];
    return sqrt((x2 - x1)*(x2-x1) + (y2-y1)*(y2-y1));
} 

void merge(int x, int y) {
    fa[find(x)] = find(y);
}

bool cmp(Edge &a, Edge &b) {
    return a.dis < b.dis;
}

int main(void) {
    std::cin >> n >> m;

    for(int i = 1; i <= n; ++i) {
        std::cin >> x[i] >> y[i];
        fa[i] = i;
    }

    int k = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = i + 1; j <=n; ++j) {
            edge[++k].x = i;
            edge[k].y = j;
            edge[k].dis = distance(i, j);
        }
    }

    int u,v;
    for(int i = 1; i <= m; ++i) {
        std::cin >> u >> v;
        edge[++k].x = u;
        edge[k]. y = v;
        edge[k].dis = 0.0;
    }

    std::sort(edge + 1, edge + 1 + k, cmp);

    double cost = 0.0;
    for(int i = 1; i <= k; ++i) {
        if(find(edge[i].x) != find(edge[i].y)) {
            merge(edge[i].x, edge[i].y);
            cost += edge[i].dis;
        }
    }

    std::cout << std::fixed << std::setprecision(2) << cost;
    return 0;
}