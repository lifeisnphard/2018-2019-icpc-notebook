/*
You are given a rooted tree with N nodes, numbered from 1 to N. Initially node 1 is the root. Each node i has a weight W[i]. You have to perform two types of operations: 
"S a" - Find the sum of weights of node a's sub-tree nodes (including node a). 
"R a" - Change root of the tree to a.
*/
#include <bits/stdc++.h>
using namespace std;
#define len(x) ((int)(x).size())

const int N = 1e5 + 10, LOGN = 18;

int weight[N], par[N][LOGN], level[N];
vector<int> adj[N];
long long sum[N];

void dfs(int u, int p){
	par[u][0] = p;
	for(int k = 1; k < LOGN; k++) par[u][k] = par[par[u][k - 1]][k - 1];
	sum[u] = weight[u];
	for(int v : adj[u]){
		level[v] = level[u] + 1;
		dfs(v, u);
		sum[u] += sum[v];
	}
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &weight[i]);
	}
	for(int i = 2; i <= n; i++){
		int p;
		scanf("%d", &p);
		adj[p].push_back(i);
	}
	dfs(1, 1);
	int q;
	scanf("%d", &q);
	int cur_root = 1;
	while(q--){
		char t; int a;
		scanf(" %c %d", &t, &a);
		if(t == 'R') cur_root = a;
		else if(cur_root == a) printf("%lld\n", sum[1]);
		else{
			int u = cur_root;
			for(int k = LOGN - 1; k >= 0; k--){
				if(level[u] - (1 << k) > level[a]) u = par[u][k];
			}
			if(par[u][0] != a) printf("%lld\n", sum[a]);
			else printf("%lld\n", sum[1] - sum[u]);
		}
	}
	return 0;
}
