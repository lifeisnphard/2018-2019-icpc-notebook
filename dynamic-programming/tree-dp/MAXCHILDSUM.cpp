/*
A rooted tree is being built. Initially, there is only one node in the tree, having number 1 and value 0. You are to perform Q (Q<=200000) queries, each of them is one of the following two types:

1 X Y - Add a new vertex to the tree with parent X (It's guaranteed that node X is already in the tree) and value Y (1<=Y<=10^9). Its number will be the smallest positive integer that is not a number of a node yet. For example, the first query of this type will add a vertex with number 2, then 3, then 4 and so on.
2 X - Consider the children of node X. For each of them, let's sum up the values of all nodes in their subtrees. You are asked to print the maximum of those sums.
*/
#include <bits/stdc++.h>
using namespace std;
#define len(x) ((int)(x).size())

const int Q = 2e5 + 10, LOGQ = 19;

int n = 1, logn;
vector<int> adj[Q];
int par[Q][LOGQ], lev[Q], ini[Q], fin[Q], euler_cnt;

void dfs(int u, int p){
	ini[u] = ++euler_cnt;
	par[u][0] = p;
	for(int k = 1; k <= logn; k++) par[u][k] = par[par[u][k - 1]][k - 1];
	for(int v : adj[u]) lev[v] = lev[u] + 1, dfs(v, u);
	fin[u] = euler_cnt;
}

long long bit[Q];

void add(int pos, int val){
	for(int i = pos; i <= n; i += (i & -i)) bit[i] += val;
}

long long sum(int pos){
	long long ret = 0;
	for(int i = pos; i >= 1; i -= (i & -i)) ret += bit[i];
	return ret;
}

long long sub[Q], ans[Q];

int main(){
	int q;
	scanf("%d", &q);
	vector<pair<int, pair<int, int>>> qry(q);
	for(int i = 0; i < q; i++){
		scanf("%d", &qry[i].first);
		if(qry[i].first == 1){
			int u, x;
			scanf("%d %d", &u, &x);
			int v = ++n;
			adj[u].push_back(v);
			qry[i].second = {v, x};
		}else{
			int u;
			scanf("%d", &u);
			qry[i].second.first = u;
		}
	}
	logn = (__builtin_clz(1) - __builtin_clz(n));
	dfs(1, 1);
	int sqrtq = sqrt(q);
	for(int i = 0; i < q; i++){
		if(qry[i].first == 1){
			int u = qry[i].second.first, x = qry[i].second.second;
			add(ini[u], x);
		}else{
			int u = qry[i].second.first;
			if(len(adj[u]) <= sqrtq){
				for(int v : adj[u]) ans[i] = max(ans[i], sum(fin[v]) - sum(ini[v] - 1));
			}
		}
	}
	for(int u = 1; u <= n; u++) if(len(adj[u]) > sqrtq){
		long long cur = 0;
		for(int i = 0; i < q; i++){
			if(qry[i].first == 1){
				int v = qry[i].second.first, x = qry[i].second.second;
				if(lev[v] > lev[u]){
					for(int k = logn; k >= 0; k--){
						if(lev[v] - (1 << k) > lev[u]) v = par[v][k];
					}
					if(u == par[v][0]) cur = max(cur, sub[v] += x);
				}
			}else{
				int v = qry[i].second.first;
				if(u == v) ans[i] = cur;
			}
		}
	}
	for(int i = 0; i < q; i++){
		if(qry[i].first == 2) printf("%lld\n", ans[i]);
	}
	return 0;
}
