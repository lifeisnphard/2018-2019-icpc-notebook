/*
Dada uma árvore com raiz que consiste de N vértices, onde cada vértice i tem um valor Vi.

Responder a M consultas: para um dado vértice X lhe dizer qual é o K-ésimo menor valor da subárvore com raiz no vértice X.
*/
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair

const int NM = 100100;

int n, a[NM], orig[NM], ans[NM];
pair<int, int> b[NM];
vector<int> adj[NM];
int subsize[NM], sc[NM];
vector<pair<int, int> > qry[NM];

struct Bit{
    int bit[NM];

    void clear(){ fill(bit + 1, bit + n + 1, 0); }

    void add(int pos, int v){
        for(int i = pos; i <= n; i += (i & -i)){
            bit[i] += v;
        }
    }

    int kth(int k){
        int pos = 0;
        for(int i = 17; i >= 0; i--){
            if(pos + (1 << i) <= n && bit[pos + (1 << i)] < k){
                k -= bit[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return orig[pos + 1];
    }
} bit;

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
    bit.add(a[u], val);
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
    if(sc[u] != -1) solve(sc[u], u);
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(v != p && v != sc[u]) addAll(v, u, 1);
    }
    bit.add(a[u], 1);
    for(int i = 0; i < qry[u].size(); i++){
        int k = qry[u][i].first, id = qry[u][i].second;
        ans[id] = bit.kth(k);
    }
}

int main(){
    //freopen("in.txt", "r", stdin);

    int t;
    scanf("%d", &t);
    while(t--){
        int m;
        scanf("%d %d", &n, &m);
        bit.clear();
        for(int i = 1; i <= n; i++){
            adj[i].clear();
            qry[i].clear();
        }
        for(int i = 1; i <= n; i++){
            scanf("%d", &a[i]);
            b[i] = mp(a[i], i);
        }
        // Compression ====================================
        sort(b + 1, b + n + 1);
        for(int i = 1; i <= n; i++){
            if(i > 1 && a[b[i - 1].second] == b[i].first){
                b[i].first = b[i - 1].first;
            }else{
                b[i].first = i;
            }
        }
        for(int i = 1; i <= n; i++){
            orig[b[i].first] = a[b[i].second];
            a[b[i].second] = b[i].first;
        }
        // ================================================
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
            qry[x].push_back(mp(k, i));
        }
        solve(1, 1);
        for(int i = 0; i < m; i++){
            printf("%d ", ans[i]);
        }
        printf("\n");
    }

    return 0;
}
