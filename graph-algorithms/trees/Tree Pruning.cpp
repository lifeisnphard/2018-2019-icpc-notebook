/*
A tree, , has  vertices numbered from  to  and is rooted at vertex . Each vertex  has an integer weight, , associated with it, and 's total weight is the sum of the weights of its nodes. A single remove operation removes the subtree rooted at some arbitrary vertex  from tree .

Given , perform up to  remove operations so that the total weight of the remaining vertices in  is maximal. Then print 's maximal total weight on a new line.

2 <= n <= 10^5, 1 <= k <= 200, -10^9 <= w_i <= 10^9
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, K = 210;

int n, k, weight[N], qtd[N];
vector<int> adj[N];
long long best[N][K], tmp[K];

void dfs(int u, int p = -1){
    qtd[u] = 1;
    for(int e = 0; e < adj[u].size(); e++){
        int v = adj[u][e];
        if(v != p){
            dfs(v, u);
            qtd[u] += qtd[v];
        }
    }
    best[u][0] = weight[u];
    for(int i = 1; i <= k; i++){
        best[u][i] = -1e15;
    }
    for(int e = 0; e < adj[u].size(); e++){
        int v = adj[u][e];
        if(v != p){
            for(int i = 0; i <= k; i++){
                tmp[i] = -1e15;
            }
            for(int i = min(k, qtd[u]); i >= 1; i--){
                tmp[i] = best[u][i - 1];
                for(int j = 0; j <= min(i, qtd[v]); j++){
                    tmp[i] = max(tmp[i], best[u][i - j] + best[v][j]);
                }
            }
            tmp[0] = best[u][0] + best[v][0];
            for(int i = 0; i <= k; i++){
                best[u][i] = tmp[i];
            }
        }
    }
}

int main(){
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++){
        scanf("%d", &weight[i]);
    }
    for(int i = 1, a, b; i < n; i++){
        scanf("%d %d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1);
    long long ans = 0;
    for(int i = 0; i <= k; i++){
        ans = max(ans, best[1][i]);
    }
    printf("%lld\n", ans);
    return 0;
}
