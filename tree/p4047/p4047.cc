#include <bits/stdc++.h>

// not solved by this file, only 50 points
// TODO bug here, but dont know where

const int MAX = 1E3 + 10;
const int MAXE = (MAX - 1) * (MAX / 2);

int k, n, x[MAX], y[MAX], cnt;

struct Edge {
    int u,v;
    double w;
};

Edge edge[MAXE];

double distance(int i, int j) {
    double dx = (double)x[i] - (double)x[j];
    double dy = (double)y[i] - (double)y[j];
    return sqrt(dx*dx + dy*dy);
}

bool cmp(Edge &a, Edge &b) {
    return a.w < b.w;
}

int fa[MAX];

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

bool check(double l) {
    for(int i = 1; i <= n; ++i) {
        fa[i] = i;
    }

    int ec = 0;
    int eqc = 0;
    for(int i = 1; i <= cnt; ++i) {
        if(edge[i].w == l) {
            eqc++;
        }

        if(find(edge[i].u) != find(edge[i].v) && edge[i].w < l) {
            merge(edge[i].u, edge[i].v);
            ++ec;
        }
    }

    return ec + eqc >= n - k && ec <= n - k;
}

int main(void) {
    std::cout.sync_with_stdio(false);
    std::cin.sync_with_stdio(false);

    std::cin >> n >> k;
    for(int i = 1; i <=n ;++i) {
        std::cin >> x[i] >> y[i];
    }

    for(int i = 1; i <=n; ++i) {
        for(int j = i + 1; j <=n; ++j) {
            edge[++cnt].u = i;
            edge[cnt].v = j;
            edge[cnt].w = distance(i, j);
        }
    }

    std::sort(edge + 1, edge + cnt + 1, cmp);

    int l = 1,r = cnt, m;
    double ans = edge[cnt].w;
    while(l <= r) {
        m = ((r - l) >> 1) + l;
        if(check(edge[m].w)) {
            l = m + 1;
            ans = edge[m].w;
        } else {
            r = m - 1;
        }
    }

    std::cout << std::fixed << std::setprecision(2) << ans;
    return 0;
}