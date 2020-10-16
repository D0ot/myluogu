#include <bits/stdc++.h>

// Not solved by this file

const int MAXN = 1E4 + 10;
const int MAXM = 2E4 + 10;

struct Edge {
    int i,n,w;
};

struct Adj {
    int e,l;
};

Edge edge[MAXM << 1];
Adj adj[MAXN];
int ep;

void add_edge(int u, int v, int w) {
    int n = ++ep;
    if(adj[u].l) {
        edge[adj[u].l].n = n;
    } else {
        adj[u].e = n;
    }
    adj[u].l = n;
    edge[n].i = v;
    edge[n].w = w;
}

int n,m,s,t;

void init() {
    std::cout.sync_with_stdio(false);
    std::cin.sync_with_stdio(false);
    std::cin >> n >> m >> s >> t;

    int u,v,w;
    for(int i = 1; i <= m; ++i) {
        std::cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
}

bool vis[MAXN];
int dis[MAXN];


struct Node {
    int p,d;

    bool operator<(const Node & rhs) const {
        return d > rhs.d;
    }

    Node(int po, int di) {
        p = po;
        d = di;
    }
};

int mint = INT_MAX;
void dijkstra() {
    for(int i = 1; i <= n; ++i) {
        vis[i] = false;
        dis[i] = INT_MAX;
    }
    // ERROR FIX
    // the error version : dis[1] = 0
    dis[s] = 0;
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

            // TODO
            // not easy learn
            int tmp = std::max(edge[e].w, dis[p]);
            if(dis[edge[e].i] > tmp) {
                dis[edge[e].i] = tmp;
                pq.emplace(edge[e].i, dis[edge[e].i]);
            }
            e = edge[e].n;
        }
    }
}


int main(void) {
    init();
    dijkstra();
    std::cout << dis[t];
    return 0;
}