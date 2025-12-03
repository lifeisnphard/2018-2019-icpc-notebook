/*
Xenia the programmer has a tree consisting of n nodes. We will consider the tree nodes indexed from 1 to n. We will also consider the first node to be initially painted red, and the other nodes — to be painted blue.

The distance between two tree nodes v and u is the number of edges in the shortest path between v and u.

Xenia needs to learn how to quickly execute queries of two types:

1. paint a specified blue node in red;
2. calculate which red node is the closest to the given one and print the shortest distance to the closest red node.

Your task is to write a program which will execute the described queries.
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, LOGN = 20, SQRTM = 320;

vector<int> adj[N], nreds;
int parent[N][LOGN], level[N], best[N];
bool vis[N];

void pre(int u, int p, int l){
    parent[u][0] = p;
    for(int k = 1; k < LOGN; k++){
        parent[u][k] = parent[parent[u][k - 1]][k - 1];
    }
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(v != p){
            pre(v, u, l + 1);
        }
    }
    level[u] = l;
}

int lca(int a, int b){
    if(level[a] < level[b]){
        swap(a, b);
    }
    for(int k = LOGN - 1; k >= 0; k--){
        if(level[a] - (1 << k) >= level[b]){
            a = parent[a][k];
        }
    }
    if(a != b){
        for(int k = LOGN - 1; k >= 0; k--){
            if(parent[a][k] != parent[b][k]){
                a = parent[a][k], b = parent[b][k];
            }
        }
        a = parent[a][0];
    }
    return a;
}

int dist(int a, int b){
    return level[a] + level[b] - 2*level[lca(a, b)];
}

void bfs(int n){
    for(int i = 1; i <= n; i++){
        vis[i] = false;
    }
    deque<pair<int, int> > dq;
    for(int i = 0; i < nreds.size(); i++){
        dq.push_back(make_pair(nreds[i], 0));
    }
    nreds.clear();
    while(!dq.empty()){
        int u = dq.front().first, d = dq.front().second; dq.pop_front();
        if(!vis[u]){
            vis[u] = true;
            best[u] = min(best[u], d);
            for(int i = 0; i < adj[u].size(); i++){
                int v = adj[u][i];
                if(!vis[v]){
                    dq.push_back(make_pair(v, d + 1));
                }
            }
        }
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 1; i < n; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    pre(1, 1, 0);
    for(int i = 1; i <= n; i++){
        best[i] = 1e9;
    }
    nreds.push_back(1);
    bfs(n);
    for(int i = 0, cnt = 0; i < m; i++){
        if(++cnt%SQRTM == 0){
            bfs(n);
        }
        int t, u;
        scanf("%d %d", &t, &u);
        if(t == 1){
            nreds.push_back(u);
        }else{
            int ans = best[u];
            for(int j = 0; j < nreds.size(); j++){
                int v = nreds[j];
                ans = min(ans, dist(u, v));
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
