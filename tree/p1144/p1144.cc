#include <bits/stdc++.h>

const int MAXN = 1E6 + 10;
const int MAXM = 2E6 + 10;

struct Edge {
    int i,n;
};

struct Adj {
    int e;
    int l;
};

Adj adj[MAXN];
Edge edge[MAXM];
int edge_pos = 1;

void add_edge(int u, int v) {
    int n = edge_pos++;
    if(adj[u].l) {
        edge[adj[u].l].n = n;
    } else {
        adj[u].e = n;
    }
    adj[u].l = n;
    edge[n].i = v;
}

int n,m,ans[MAXN], vis[MAXN], dis[MAXN];

struct Node {
    int p,d;
    bool operator<(const Node& rhs) const {
        return d > rhs.d;
    }

    Node(int pos, int dis) {
        p = pos;
        d = dis;
    }

};

void dijkstra(int s) {
    std::priority_queue<Node> pq;
    pq.emplace(s, 0);
    while(!pq.empty()) {
        int p = pq.top().p;
        pq.pop();
        if(vis[p]) {
            continue;
        }
        vis[p] = true;

        int e = adj[p].e;
        while(e) {
            if(dis[edge[e].i] > dis[p] + 1) {
                dis[edge[e].i] = dis[p] + 1;
                pq.emplace(edge[e].i, dis[edge[e].i]);
                ans[edge[e].i] = ans[p];
            } else if (dis[edge[e].i] == dis[p] + 1) {
                ans[edge[e].i] += ans[p];
                ans[edge[e].i] %= 100003;
            }
            e = edge[e].n;
        }
    }
}

int main(void) {
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(true);

    std::cin >> n >> m;
    int u,v;
    for(int i = 0; i < m; ++i){
        std::cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    dis[1] = 0;
    for(int i = 2; i <= n; ++i) {
        dis[i] = INT_MAX;
    }
    ans[1] = 1;

    dijkstra(1);

    for(int i = 1; i <= n; ++i) {
        std::cout << ans[i] << '\n';
    }
    return 0;
}
