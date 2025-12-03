/*
You are given a tree with N nodes, and edges numbered 1, 2, 3...N-1. Each edge has an integer value assigned to it, representing its length.

We will ask you to perfrom some instructions of the following form:

DIST a b : ask for the distance between node a and node b
or
KTH a b k : ask for the k-th node on the path from node a to node b
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10, LOGN = 15;

vector<pair<int, int> > adj[N];
int logN, parent[N][LOGN], dist[N], height[N];

void dfs(int u, int p, int d = 0, int h = 0){
    dist[u] = d;
    height[u] = h;
    parent[u][0] = p;
    for(int k = 1; k <= logN; k++){
        parent[u][k] = parent[parent[u][k - 1]][k - 1];
    }
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i].first, cost = adj[u][i].second;
        if(v != p) dfs(v, u, d + cost, h + 1);
    }
}

int up(int u, int h){
    for(int k = logN; k >= 0; k--){
        if(height[u] - (1 << k) >= h){
            u = parent[u][k];
        }
    }
    return u;
}

int lca(int a, int b){
    if(height[a] < height[b]) swap(a, b);
    a = up(a, height[b]);
    if(a == b) return a;
    for(int k = logN; k >= 0; k--){
        if(parent[a][k] != parent[b][k]){
            a = parent[a][k], b = parent[b][k];
        }
    }
    return parent[a][0];
}

int kth(int a, int b, int k){
    int anc = lca(a, b);
    if(height[a] - height[anc] < k){
        k -= height[a] - height[anc];
        k = height[b] - height[anc] - k;
        swap(a, b);
    }
    return up(a, height[a] - k);
}

int main(){
    int t;
    scanf("%d", &t);
    for(int k = 0, n; k < t; k++){
        scanf("%d", &n);
        logN = log2(n);
        for(int i = 1, a, b, c; i < n; i++){
            scanf("%d %d %d", &a, &b, &c);
            adj[a].push_back(make_pair(b, c));
            adj[b].push_back(make_pair(a, c));
        }
        dfs(1, 1);
        char s[10];
        while(scanf("%s", &s) && strcmp(s, "DONE")){
            if(!strcmp(s, "DIST")){
                int a, b;
                scanf("%d %d", &a, &b);
                printf("%d\n", dist[a] + dist[b] - 2*dist[lca(a, b)]);
            }else{
                int a, b, k;
                scanf("%d %d %d", &a, &b, &k);
                printf("%d\n", kth(a, b, k - 1));
            }
        }
        printf("\n");
        for(int i = 1; i <= n; i++){
            adj[i].clear();
        }
    }
    return 0;
}
