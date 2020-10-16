#include <bits/stdc++.h>


const int MAX = 5E5 + 10;

struct Edge{
    int i;
    int n; 
};

struct Adj {
    int e;
    int l;
};


Adj adj[MAX];
Edge edge[MAX*2];
bool has[MAX];

int edge_pos = 1;

void add_edge(int u, int v) {
    int n = edge_pos++;
    if(adj[u].l == 0) {
        adj[u].e = n;
        adj[u].l = n;
    } else {
        edge[adj[u].l].n = n;
        adj[u].l = n;
    }
    edge[n].i = v;
}

#ifdef MYDEBUG
void test_dfs(int k) {
    if(has[k]) {
        return;
    } else {
        has[k] = true;
    }
    std::cout << k << ' ';

    int p = adj[k].e;
    while(p) {
        test_dfs(edge[p].i);
        p = edge[p].n;
    }
}
#endif

int height[MAX];

int fa[MAX][22];


void dfs(int s, int h) {
    int p = adj[s].e;
    height[s] = h;
    int l;
    if(h) {
        l = std::log2(h);
    }else {
        l = 0;
    }

    for(int i = 1; i <= l; ++i) {
        fa[s][i] = fa[fa[s][i-1]][i-1];
    }

    while(p) {
        if(!has[edge[p].i]) {
            has[edge[p].i] = true;
            fa[edge[p].i][0] = s;
            dfs(edge[p].i, h + 1);
        }
        p = edge[p].n;
    }

}

int query(int u, int v){
    if(height[u] < height[v]) {
        std::swap(u, v);
    }

    #ifdef MYDEBUG
    std::cout << "u, v = " << u << ", " << v << std::endl;
    #endif

    while(height[u] > height[v]) {
        u = fa[u][(int)log2(height[u] - height[v])];
    }

    if(u == v) {
        return u;
    }
    
    #ifdef MYDEBUG
    std::cout << "u, v = " << u << ", " << v << std::endl;
    #endif

    
    int l = log2(height[u]);

    while(u != v && l >= 0) {

        #ifdef MYDEBUG
        std::cout << "u, v = " << u << ", " << v << std::endl;
        std::cout << "l = " << l <<std::endl;
        #endif

        if(fa[u][l] == fa[v][l]) {
            // should go down to try
            --l;
        } else {
            // should go up
            u = fa[u][l];
            v = fa[v][l];
            l = log2(height[u]);
        }
    }


    /*
    for(int l = log2(height[u]); l >=0; --l) {
        if(fa[u][l] != fa[v][l]) {
            u = fa[u][l];
            v = fa[v][l];
        }
    }*/

    return fa[u][0];
}

int main() {
    std::ios::sync_with_stdio(false);   
    std::cin.tie(0);    // IO
    int n,m,s;
    std::cin >> n >> m >> s;

    int t,k;
    for(int i = 1; i < n; ++i) {
        std::cin >> t >> k;
        add_edge(t, k);
        add_edge(k, t);
    }

    

    for(int i = 0; i < 22; ++i) {
        fa[s][i] = s;
    }
    // h is diff of height to root, so height of root is 0
    
    #ifdef MYDEBUG
    std::cout << "dfs\n";
    #endif

    has[s] = true;
    dfs(s, 0);


    #ifdef MYDEBUG
    for(int j = 1; j <= n; ++j) {
        std::cout << std::left << std::setw(3) << j << ' ';
    }
    std::cout << std::endl;

    for(int i = 0; i < 10; ++i) {
        for(int j = 1; j <= n; ++j) {
            std::cout << std::left << std::setw(3) << fa[j][i] << ' ';
        }
        std::cout <<std::endl;
    }
    #endif

    int qx, qy;
    for(int i = 1; i <= m; ++i) {
        std::cin >> qx >> qy;
        if(qx == s || qy == s) {
            std::cout << s << '\n';
        } else if(qx == qy){
            std::cout << qx << '\n';
        } else {
            std::cout << query(qx, qy) << '\n';
        }
    }

    return 0; 
}

