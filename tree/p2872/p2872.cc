#include <bits/stdc++.h>

// not solved not this file, TLE and WA, 60 points gotten

const int MAX = 1E3 + 10;

int n,m;
int k = 1;

int x[MAX], y[MAX];
double dis[MAX][MAX];

int u[MAX * MAX], v[MAX * MAX];
int so[MAX * MAX];
int fa[MAX];


double distance(int i, int j) {
    double dx = x[j] - x[i];
    double dy = y[j] - y[i];
    return sqrt(dx*dx + dy*dy);
}

bool cmp(int ia, int ib) {
    ia = so[ia];
    ib = so[ib];
    return dis[u[ia]][v[ia]] < dis[u[ib]][v[ib]];
}

void init() {
    std::cout.sync_with_stdio(false);
    std::cin.sync_with_stdio(false);

    std::cin >> n >> m;

    for(int i = 1; i <=n; ++i) {
        std::cin >> x[i] >> y[i];
    }

    for(int i = 1; i <= n; ++i) {
        fa[i] = i;
        for(int j = i + 1; j <= n; ++j) {
            u[k] = i;
            v[k] = j;
            dis[j][i] = dis[i][j] = distance(i, j);
            so[k] = k;
            ++k;
        }
    }
    int u,v;
    for(int i = 1; i <= m; ++i) {
        std::cin >> u >> v;
        dis[u][v] = 0;
    }

    std::sort(so + 1, so + k + 1, cmp);

}


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

long double kruskal() {
    int i = 1;
    int cnt = 0;
    long double cost = 0.0f;
    int j;
    while(i <= k && cnt != n - 1) {
        j = so[i];
        if(find(u[j]) != find(v[j])) {
            merge(u[j], v[j]);
            cnt++;
            cost += dis[u[j]][v[j]];
        }
        ++i;
    }
    return cost;
}

int main() {
    init();
    std::cout << std::fixed << std::setprecision(2) << kruskal();
    return 0;
}
