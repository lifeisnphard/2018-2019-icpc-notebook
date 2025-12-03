/*
Dada uma árvore com raiz que consiste de N vértices, onde cada vértice i tem um valor Vi.

Responder a M consultas: para um dado vértice X lhe dizer qual é o K-ésimo menor valor da subárvore com raiz no vértice X.
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int NM = 100100;

int n, a[NM], ans[NM];
vector<int> adj[NM];
int subsize[NM], sc[NM];
vector<pair<int, int> > qry[NM];

ordered_set<pair<int, int>> treap;

void dfs(int u, int p){
    subsize[u] = 1, sc[u] = -1;
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(v != p){
            dfs(v, u);
            subsize[u] += subsize[v];
            if(sc[u] == -1 || subsize[v] > subsize[sc[u]]){
                sc[u] = v;
            }
        }
    }
}

void addAll(int u, int p, int val){
    if(val == 1) treap.insert({a[u], u});
    else treap.erase({a[u], u});
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(v != p) addAll(v, u, val);
    }
}

void solve(int u, int p){
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(v != p && v != sc[u]){
            solve(v, u);
            addAll(v, u, -1);
        }
    }
    if(sc[u] != -1){
        solve(sc[u], u);
        for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(v != p && v != sc[u]) addAll(v, u, 1);
        }
    }
    treap.insert({a[u], u});
    for(int i = 0; i < qry[u].size(); i++){
        int k = qry[u][i].first, id = qry[u][i].second;
        ans[id] = treap.find_by_order(k - 1)->first;//treap.kth(k);
    }
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int m;
        scanf("%d %d", &n, &m);
        treap.clear();
        for(int i = 1; i <= n; i++){
            adj[i].clear();
            qry[i].clear();
        }
        for(int i = 1; i <= n; i++){
            scanf("%d", &a[i]);
        }
        for(int i = 1; i < n; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(1, 1);
        for(int i = 0; i < m; i++){
            int x, k;
            scanf("%d %d", &x, &k);
            qry[x].push_back({k, i});
        }
        solve(1, 1);
        for(int i = 0; i < m; i++){
            printf("%d ", ans[i]);
        }
        printf("\n");
    }

    return 0;
}
