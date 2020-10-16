#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <utility>

const int MAX = 300000;
struct Edge {
    int i; // index
    Edge *next; //next edge

    Edge() {
        i = 0;
        next = nullptr;
    }
};

struct Adj {
    int s; // start;
    Edge *e; // edge;
    Edge *last;

    Adj() {
        s = 0;
        e = nullptr;
        last = nullptr;
    }
};

Adj adj[MAX];
int max_adj = 0;
Edge edges[MAX];
int edge_pos = 0;

std::unordered_set<int> set;

Edge *next_edge() {
    return edges + edge_pos++;
}

void add_single_edge(int t, int k) {
    if(adj[t].last) {
        auto p = adj[t].last;
        p->next = next_edge();
        adj[t].last = p->next;
        p->next->i = k;
    } else {
        adj[t].s = t;
        adj[t].e = next_edge();
        adj[t].last = adj[t].e;
        adj[t].e->i = k;
    }
}

char prefer;
std::string str;
std::vector<int> path;
std::unordered_map<std::pair<int, int>, uint8_t> map;


bool dfs(int start, int end) {
    if(set.find(start) != set.end()) {
        return false;
    }

    path.push_back(start);

    if(start == end) {
        path.push_back(start);
        return true;
    }

    auto p = adj[start].e;
    set.insert(start);
    while(p) {
        auto ret = dfs(p->i, end);
        if(ret) {
            return true;
        }
        p = p->next;
    }
    set.erase(start);
    path.pop_back();
    return false;
}



int main(void) {
    int n, m;
    std::cin >> n >> m;

    #ifdef DEBUG
    std::cout << n << ' ' << m << std::endl;
    #endif
    
    std::cin >> str;

    #ifdef DEBUG
    std::cout << str << std::endl;
    #endif

    int t, k;
    char c;
    for(auto i = 0; i < n - 1; ++i) {
        std::cin >> t >> k;
        #ifdef DEBUG
        max_adj = std::max(max_adj, std::max(t, k));
        std::cout << t << ' ' << k << std::endl;
        #endif
        add_single_edge(t, k);
        add_single_edge(k, t);
    }

    #ifdef DEBUG
    for(auto i = 1; i < max_adj; ++i) {
        std::cout << adj[i].s << " : ";

        auto p = adj[i].e;
        decltype(p) rec;
        while(p) {
            std::cout << p->i << ", ";
            rec = p;
            p = p->next;
        }
        std::cout << (rec == adj[i].last) << std::endl;
    }
    #endif

    bool flag;
    for(auto i = 0; i < m; ++i) {
        std::cin >> t >> k >> prefer;
        flag = false;
        set.clear();
        path.clear();
        dfs(t,k);

        for(auto && x : path) {
            if(str[x-1] == prefer) {
                flag = true;
                break;
            }
        }
        std::cout << flag;

        

    }
    return 0;
}