/*
You are given a tree consisting of N nodes, each node i has a value a[i] (0 ≤ a[i] ≤ 1) associated with it.

We call a set S of tree nodes beautiful if following conditions are satisfied:

S is non-empty.
S is connected. In other words, if nodes u and v are in S, then all nodes lying on the simple path between u and v should also be presented in S.
Sum of all a[u] (u belong to S) equals to K where K is a given integer.
Your task is to count the number of beautiful sets. Since the answer may very large, you should print it modulo 109 + 7.

1 ≤ SN ≤ 50000, 1 ≤ K ≤ 100
*/
#include <bits/stdc++.h>
using namespace std;
 
const int N = 5e4 + 10, K = 110, MOD = 1e9 + 7;
 
int n, k, a[N];
vector<int> adj[N];
int qtd[N], dp[N][K], tmp[K];
 
void dfs(int u, int p){
	qtd[u] = 1;
	for(auto v : adj[u]) if(v != p){
		dfs(v, u);
		qtd[u] += qtd[v];
	}
	for(int i = 0; i <= k; i++) dp[u][i] = 0;
	dp[u][a[u]] = 1;
	for(int v : adj[u]) if(v != p){
		for(int i = 0; i <= min(k, qtd[u]); i++) tmp[i] = dp[u][i];
		for(int i = 0; i <= min(k, qtd[u]); i++){
			for(int j = 0; j <= min(i, qtd[v]); j++){
				tmp[i] = (tmp[i] + dp[u][i - j]*1LL*dp[v][j])%MOD;
			}
		}
		for(int i = 0; i <= min(k, qtd[u]); i++) dp[u][i] = tmp[i];
	}
}
 
int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &k);
		for(int i = 1; i <= n; i++){
			scanf("%d", &a[i]);
			adj[i].clear();
		}
		for(int i = 1; i < n; i++){
			int u, v;
			scanf("%d %d", &u, &v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		dfs(1, 1);
		int ans = 0;
		for(int i = 1; i <= n; i++){
			ans = (ans + dp[i][k])%MOD;
		}
		printf("%d\n", ans);
	}
	return 0;
}
