#include <bits/stdc++.h>

const int MAXN = 2E2 + 10;
const int MAXM = (MAXN * (MAXN -1))/2;

int dis[MAXN][MAXN];
int times[MAXN];

int n,m,q;

// floyd可以一个一个地进行k
void floyd(int k) {
    for(int i = 0; i <= n; ++i) {
        for(int j = 0; j <= n; ++j) {
            if(dis[i][k] == INT_MAX || dis[k][j] == INT_MAX) {
                continue;
            }
            if(dis[i][j] > dis[i][k] + dis[k][j]) {
                dis[j][i] = dis[i][j] = dis[i][k] + dis[k][j];
            }
        }
    }
}

int main(void) {

    std::cin.tie(0);
    std::cout.sync_with_stdio(false);

    std::cin >> n >> m;
    
    for(int i = 0; i < n; ++i) {
        std::cin >> times[i];
    }
    times[n] = INT_MAX;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            dis[i][j] = INT_MAX;
        }
    }

    for(int i = 0; i < n; ++i) {
        dis[i][i] = 0;
    }

    int x,y,t;
    for(int i = 0; i < m; ++i) {
        std::cin >> x >> y;
        std::cin >> dis[x][y];
        dis[y][x] = dis[x][y];
    }
    std::cin >> q;

    int cur = 0;
    for(int i = 0; i < q; ++i) {
        std::cin >> x >> y >> t;
        while(times[cur] <= t) {
            floyd(cur);
            cur++;
        }
        
        if(dis[x][y] == INT_MAX || times[x] > t || times[y] > t) {
            std::cout << -1 << '\n';
        } else {
            std::cout << dis[x][y] << '\n';
        }
    }
    return 0;
}