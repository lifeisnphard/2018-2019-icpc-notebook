/*
Ao planejar as rotas, a SBC se deparou com um problema: por razões de segurança, cada ponte da Nlogônia tem um limite máximo de peso permitido para os veículos que trafegam sobre ela. Devido ao grande número de pontes na Nlogônia, e ao elevado peso da mercadoria transportada, o diretor de operações da SBC pediu que você escrevesse um programa que determina o maior peso bruto que pode ser transportado entre os depósitos e os locais de prova.
*/
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <set>
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;

const int INF = 0x3f3f3f3f;
const int MAXN = 20010, MAXM = 100010, MAXLOGN = 20;

bool mark[MAXM], visit[MAXN];
int logN, dist[MAXN], cost[MAXM];
int nivel[MAXN], pai[MAXN][MAXLOGN], mincost[MAXN][MAXLOGN];
vector<ii> adj[MAXN];

void inverse_prim(int n){
    set<iii,greater<iii> > s;
    for(int i = 1; i <= n; i++){
        visit[i] = false;
        dist[i] = -1;
    }
    dist[1] = 0;
    s.insert(iii(0,ii(1,0)));
    while(!s.empty()){
        iii aux = *s.begin(); s.erase(s.begin());
        int u = aux.second.first, e = aux.second.second;

        if(visit[u]) continue;
        visit[u] = true;
        mark[e] = true;

        int tam = adj[u].size();
        for(int i = 0; i < tam; i++){
            int v = adj[u][i].first, en = adj[u][i].second;
            if(!visit[v] and cost[en]>dist[v]){
                dist[v] = cost[en];
                s.insert(iii(cost[en],ii(v,en)));
            }
        }
    }
}

void dfs(int u, int p, int d, int l){
    nivel[u] = l;
    pai[u][0] = p;
    mincost[u][0] = d;
    for(int k = 1; k <= logN; k++){
        pai[u][k] =  pai[ pai[u][k-1] ][k-1];
        mincost[u][k] = min(mincost[u][k-1],mincost[ pai[u][k-1] ][k-1]);
    }

    int tam = adj[u].size();
    for(int i = 0; i < tam; i++){
        int v = adj[u][i].first, e = adj[u][i].second;
        if(v!=p and mark[e]) dfs(v,u,cost[e],l+1);
    }
}

int lca(int a, int b){
    int resp = INF;
    if(nivel[a]<nivel[b]) swap(a,b);
    for(int k = logN; k >= 0; k--){
        if(nivel[a]-(1<<k)>=nivel[b]){
            resp = min(resp,mincost[a][k]);
            a = pai[a][k];
        }
    }
    if(a==b) return resp;
    for(int k = logN; k >= 0; k--){
        if(pai[a][k]!=pai[b][k]){
            resp = min(resp,min(mincost[a][k],mincost[b][k]));
            a = pai[a][k], b = pai[b][k];
        }
    }
    resp = min(resp,min(mincost[a][0],mincost[b][0]));
    return resp;
}

int main(){
    int n, m, s, a, b, p;

    while(scanf("%d %d %d", &n, &m, &s)!=EOF){
        logN = log2(n);
        for(int i = 1; i <= n; i++)
            adj[i].clear();
        for(int i = 1; i <= m; i++){
            scanf("%d %d %d", &a, &b, &p);
            cost[i] = p;
            mark[i] = false;
            adj[a].push_back(ii(b,i));
            adj[b].push_back(ii(a,i));
        }
        inverse_prim(n);
        dfs(1,1,INF,0);
        while(s--){
            scanf("%d %d", &a, &b);
            printf("%d\n", lca(a,b));
        }
    }

    return 0;
}
