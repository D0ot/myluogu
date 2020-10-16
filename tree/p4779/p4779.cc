#include <bits/stdc++.h>

//reference : https://www.luogu.com.cn/problem/solution/P4779

const int MAXN = 1E5 + 10;
const int MAXM = 5E5 + 10;

struct Edge {
    int i,w,n;
};

struct Adj {
    int e,l;
};

Edge edges[MAXM];
Adj adjs[MAXN];
int edge_pos = 1;
int dis[MAXN];
bool vis[MAXN];

void add_edge(int u, int v, int w) {
    int n = edge_pos++;
    if(adjs[u].l) {
        edges[adjs[u].l].n = n;
        adjs[u].l = n;
    } else {
        adjs[u].e = n;
        adjs[u].l = n;
    }
    edges[n].i = v;
    edges[n].w = w;
}

struct Node {
    int p;
    int d;
    bool operator <(const Node& rhs) const {
        return d > rhs.d;
    }

    Node(int pos, int dis) {
        p = pos;
        d = dis;
    }
};

// why use a priority_queue
std::priority_queue<Node> pq;

void dijkstra(int s) {
    dis[s] = 0;
    pq.emplace(s, 0);
    while(!pq.empty()) {
        int p = pq.top().p;
        int d = pq.top().d;
        pq.pop();
        if(vis[p]) {
            continue;
        }
        vis[p] = true;

        int e = adjs[p].e;
        while(e) {
            int n = edges[e].i;
            if(dis[n] > dis[p] + edges[e].w) {
                dis[n] = dis[p] + edges[e].w;
                pq.emplace(n, dis[n]);
            }
            e = edges[e].n;
        }
    }
}

int main(void) {
    int n,m,s;
    std::cin >> n >> m >> s;
    int u,v,w;
    
    for(int i = 1; i <= m; ++i) {
        std::cin  >> u >> v >> w;
        add_edge(u, v, w);
    }

    for(int i = 1; i <= n; ++i) {
        dis[i] = INT_MAX;
    }
    dijkstra(s);
    for(int i = 1; i <n; ++i) {
        std::cout << dis[i] << ' ';
    }
    std::cout << dis[n];
}
