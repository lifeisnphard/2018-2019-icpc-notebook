/*
Chef has a undirected graph G. This graph consists of N vertices and M edges. Each vertex of the graph has an unique index from 1 to N, also each edge of the graph has an unique index from 1 to M.

Also Chef has Q pairs of integers: Li, Ri (1 ≤ Li ≤ Ri ≤ M). For each pair Li, Ri, Chef wants to know: how many connected components will contain graph G if Chef erase all the edges from the graph, except the edges with indies X, where Li ≤ X ≤ Ri. Please, help Chef with these queries.
*/
#include <bits/stdc++.h>
using namespace std;

const int NMQ = 2e5 + 10, SQRTM = 450;

vector<int> adj[NMQ];
pair<int, int> edge[NMQ];
vector<pair<pair<int, int>, int>> qry[SQRTM], mod;
int parent[NMQ], rnk[NMQ], ans[NMQ];

int fnd(int x, bool def){
    if(parent[x] == x){
        return x;
    }
    if(!def) mod.push_back(make_pair(make_pair(x, parent[x]), -1));
    return parent[x] = fnd(parent[x], def);
}

bool join(int a, int b, bool def){
    a = fnd(a, def), b = fnd(b, def);
    if(a == b){
        return false;
    }
    bool added = false;
    if(rnk[a] < rnk[b]){
        swap(a, b);
    }else if(rnk[a] == rnk[b]){
        rnk[a]++;
        added = true;
    }
    if(!def) mod.push_back(make_pair(make_pair(b, parent[b]), added? a : -1));
    parent[b] = a;
    return true;
}

void add(int &ans, int idx, bool def){
    if(join(edge[idx].first, edge[idx].second, def)){
        ans--;
    }
}

int main(){
    //freopen("in.txt", "r", stdin);

    int t;
    scanf("%d", &t);
    while(t--){
        int n, m, q;
        scanf("%d %d %d", &n, &m, &q);
        for(int i = 0, u, v; i < m; i++){
            scanf("%d %d", &u, &v);
            edge[i] = make_pair(u, v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int sqrtm = sqrt(m);
        for(int i = 0, l, r; i < q; i++){
            scanf("%d %d", &l, &r); l--, r--;
            qry[l/sqrtm].push_back(make_pair(make_pair(r, l), i));
        }
        for(int i = 0; i <= (m - 1)/sqrtm; i++){
            sort(qry[i].begin(), qry[i].end());
            for(int j = 1; j <= n; j++){
                parent[j] = j;
                rnk[j] = j;
            }
            for(int j = 0, nxt = (i + 1)*sqrtm, curAns = n; j < qry[i].size(); j++){
                int l = qry[i][j].first.second, r = qry[i][j].first.first, idx = qry[i][j].second;
                while(nxt <= r){
                    add(curAns, nxt, true);
                    nxt++;
                }
                int tmp = curAns;
                for(int k = l; k <= min(r, (i + 1)*sqrtm - 1); k++){
                    add(tmp, k, false);
                }
                ans[idx] = tmp;
                for(int k = mod.size() - 1; k >= 0; k--){
                    int b = mod[k].first.first, old = mod[k].first.second, a = mod[k].second;
                    parent[b] = old;
                    if(a != -1) rnk[a]--;
                }
                mod.clear();
            }
            qry[i].clear();
        }
        for(int i = 0; i < q; i++){
            printf("%d\n", ans[i]);
        }
        for(int i = 1; i <= n; i++){
            adj[i].clear();
        }
    }
    return 0;
}
