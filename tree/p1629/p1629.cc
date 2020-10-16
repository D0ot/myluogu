#include <bits/stdc++.h>

const int MAXN = 1E3 + 10;
const int MAXM = 1E5 + 10;

struct Edge {
    int i,n,w;
};

struct Adj {
    int l;
    int e;
};

Adj adj1[MAXN];
Edge edge1[MAXM];
int dis1[MAXN];
int edge_pos1 = 1;
bool has1[MAXN];


Adj adj2[MAXN];
Edge edge2[MAXM];
int dis2[MAXN];
int edge_pos2 = 1;
bool has2[MAXN];

void add_edge(int u, int v, int w) {
    int n1 = edge_pos1++;
    if(adj1[u].l) {
        edge1[adj1[u].l].n = n1;
        adj1[u].l = n1;
    } else {
        adj1[u].e = n1;
        adj1[u].l = n1;
    }
    edge1[n1].i = v;
    edge1[n1].w = w;

    int n2= edge_pos2++;
    if(adj2[v].l) {
        edge2[adj2[v].l].n = n2;
        adj2[v].l = n2;
    } else {
        adj2[v].e = n2;
        adj2[v].l = n2;
    }
    edge2[n2].i = u;
    edge2[n2].w = w; 
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
    Node(const Node &n){
        p = n.p;
        d = n.d;
    }
    
};

void dijkstra(Adj *adj, Edge *edge, int *dis, bool *has, int s) {
    std::priority_queue<Node> pq;
    pq.emplace(s, 0);
    while(!pq.empty()) {
        Node tmp = pq.top();
        pq.pop();
        int p = tmp.p;
        if(has[p]) {
            continue;
        }
        has[p] = true;

        int iter = adj[p].e;
        
        while(iter) {
            if(dis[edge[iter].i] > dis[p] + edge[iter].w) {
                dis[edge[iter].i] = dis[p] + edge[iter].w;
                pq.emplace(edge[iter].i, dis[edge[iter].i]);
            }
            iter = edge[iter].n;
        }
    }
}


int main(void) {
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);
    std::cin >> n >> m;

    int u,v,w;
    for(int i = 0; i < m; ++i) {
        std::cin >> u >> v >> w;
        add_edge(u, v, w);
    }

    for(int i = 2; i <= n; ++i) {
        dis1[i] = dis2[i] = INT_MAX;
    }
    dis1[1] = dis2[1] = 0;

    dijkstra(adj1, edge1, dis1, has1, 1);
    dijkstra(adj2, edge2, dis2, has2, 1);

    int tsum = 0;
    for(int i = 1; i <= n; ++i) {
        tsum += dis1[i] + dis2[i];
    }
    std::cout << tsum;
}
