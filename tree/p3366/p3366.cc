#include <bits/stdc++.h>

const int MAXN = 5E3 + 10;
const int MAXM = 2E5 + 10;

struct Edge{
    int i, n, w;
};


struct Adj {
    int e,l;
};

Edge edge[MAXM << 1];
Adj adj[MAXN];
int vis[MAXN];
int edge_pos;

void add_edge(int u, int v, int w) {
    int n = ++edge_pos;
    if(adj[u].l) {
        edge[adj[u].l].n = n;
    } else {
        adj[u].e = n;
    }
    adj[u].l = n;
    edge[n].i = v;
    edge[n].w = w;
}

int n,m;

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


int cnt = 0;
int prim(int s) {
    std::priority_queue<Node> pq;
    int sum = 0;
    pq.emplace(s, 0);
    while(!pq.empty()) {
        int p = pq.top().p;
        int d = pq.top().d;
        pq.pop();
        if(vis[p]) {
            continue;
        }
        vis[p] = true;
        cnt++;
        sum += d;
        int e = adj[p].e;
        while(e) {
            if(!vis[edge[e].i]) {
                pq.emplace(edge[e].i, edge[e].w);
            }
            e = edge[e].n;
        }
    }
    if(cnt != n) {
        return -1;
    } else {
        return sum;
    }
}

void init() {
    scanf("%d%d", &n, &m);
    int u,v,w;
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
}

int main() {
    init();
    int ret = prim(1);
    if(ret != -1) {
        printf("%d", ret);
    } else {
        printf("orz");
    }
    return 0;
}


