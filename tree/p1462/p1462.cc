#include <bits/stdc++.h>

// 出错原因
// 边的数量是M的两倍，因为是无向图
// 二分查找的出口条件是 “小于等于”
// 如果有跳过，那么一定要检查是不是有错误的地方


// 最大的问题是：
// 多次使用的数组得进行初始化。每个都要进行。从1到N每个都要进行初始化。
// 本题中的vis每次初始化不完全导致WA

const int MAXN = 1E4+10;
const int MAXM = 5E4+10;

struct Edge {
    int w,n,i;
};

struct Adj {
    int e,l;
};

int n,m,b;

Adj adj[MAXN];
Edge edge[MAXM * 2];
int edge_pos = 1;
bool vis[MAXN];
long long fee[MAXN], dis[MAXN], fs[MAXN];


void add_edge(int u, int v, int w) {
    int n = edge_pos++;
    if(adj[u].l) {
        edge[adj[u].l].n = n;
    } else {
        adj[u].e = n;
    }
    adj[u].l = n;
    edge[n].i = v;
    edge[n].w = w;
}

struct Node {
    int p;
    long long d;
    bool operator<(const Node & rhs) const {
        return d > rhs.d;
    }

    Node(int pos, long long dis) {
        p = pos;
        d = dis;
    }
};


bool dijkstra(int x) {
    if(fee[1] > x || fee[n] > x) {
        return false;
    }
    for(int i = 0; i <= n; ++i) {
        dis[i] = LLONG_MAX;
        if(fee[i] > x) {
            vis[i] = true;
        }else {
            vis[i] = false;
        }
    }
    dis[1] = 0;

    std::priority_queue<Node> pq;
    pq.emplace(1, 0);
    while(!pq.empty()) {
        int p = pq.top().p;
        pq.pop();
        if(vis[p]) {
            continue;
        }
        vis[p] = true;

        int e = adj[p].e;
        while(e) {
            if(dis[p] == LONG_MAX || edge[e].w == LONG_MAX) {
                continue;
            }

            if(dis[edge[e].i] > dis[p] + edge[e].w) {
                dis[edge[e].i] = dis[p] + edge[e].w;
                pq.emplace(edge[e].i, dis[edge[e].i]);
            }
            e = edge[e].n;
        }
    }

    if(dis[n] < b) {
        return true;
    } else {
        return false;
    }

}

int main(void) {
    std::cout.sync_with_stdio(false);
    std::cin.sync_with_stdio(false);
    
    std::cin >> n >> m >> b;
    for(int i = 1; i <= n; ++i) {
        std::cin >> fee[i];
        fs[i] = fee[i];
    }


    int u,v;
    long long w;
    for(int i = 1; i <= m; ++i) {
        std::cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    if(!dijkstra(INT_MAX)) {
        std::cout << "AFK";
        return 0;
    }
    std::sort(fs + 1, fs + n + 1);

    int l = 1,r = n,m;
    long long ans = fs[n];
    while(l <= r) {
        m = ((r - l) / 2) + l;
        if(dijkstra(fs[m])) {
            ans = fs[m];
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    std::cout << ans;
    return 0;
}





