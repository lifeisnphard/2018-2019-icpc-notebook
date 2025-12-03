/*
Minimal path in a graph that doesn't use any edge that belong to some minimal path.
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 510, M = 1e4 + 10;

vector<pair<int, int> > adj[N], parents[N];
int cost[M], dist[N];
bool blocked[M], vis[N];

void dijkstra(int u, int n){
    for(int i = 0; i < n; i++){
        dist[i] = 1 << 30;
    }
    dist[u] = 0;
    set<pair<int, int> > s;
    s.insert(make_pair(0, u));
    while(!s.empty()){
        pair<int, int> aux = *s.begin(); s.erase(s.begin());
        int d = aux.first, u = aux.second;

        if(d > dist[u]) continue;

        for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i].first, e = adj[u][i].second;
            if(!blocked[e] && dist[u] + cost[e] < dist[v]){
                dist[v] = dist[u] + cost[e];
                s.insert(make_pair(dist[v], v));
            }
        }
    }
}

int main(){
    int n, m;
    while(scanf("%d %d", &n, &m)){
        if(n == 0 && m == 0) break;
        int s, d;
        scanf("%d %d", &s, &d);
        for(int i = 0, u, v; i < m; i++){
            scanf("%d %d %d", &u, &v, &cost[i]);
            adj[u].push_back(make_pair(v, i));
            parents[v].push_back(make_pair(u, i));
            blocked[i] = false;
        }
        dijkstra(s, n);
        // Exclui arestas do menor caminho ---------------------
        deque<int> dq;
        dq.push_back(d);
        while(!dq.empty()){
            int v = dq.front(); dq.pop_front();

            vis[v] = true;

            for(int i = 0; i < parents[v].size(); i++){
                int u = parents[v][i].first, e = parents[v][i].second;
                if(!vis[u] && dist[u] + cost[e] == dist[v]){
                    blocked[e] = true;
                    dq.push_back(u);
                }
            }
        }
        // -----------------------------------------------------
        dijkstra(s, n);
        printf("%d\n", (dist[d] < (1 << 30))? dist[d] : -1);
        for(int i = 0; i < n; i++){
            parents[i].clear();
            adj[i].clear();
            vis[i] = false;
        }
    }

    return 0;
}
