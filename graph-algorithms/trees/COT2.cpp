/*
You are given a tree with N nodes. The tree nodes are numbered from 1 to N. Each node has an integer weight.

We will ask you to perform the following operation:

u v : ask for how many different integers that represent the weight of nodes there are on the path from u to v.
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 4e4 + 10, LOGN = 17, SQRT2N = 285, M = 1e5 + 10;

int weight[N];
vector<int> adj[N];
int parent[N][LOGN], level[N];
int ini[N], fin[N], node_cnt, idx[2*N];

void dfs(int u, int p, int l){
	parent[u][0] = p;
	for(int k = 1; k < LOGN; k++){
		parent[u][k] = parent[parent[u][k - 1]][k - 1];
	}
	level[u] = l;
	ini[u] = node_cnt++;
	for(int v : adj[u]) if(v != p){
		dfs(v, u, l + 1);
	}
	fin[u] = node_cnt++;
	idx[ini[u]] = idx[fin[u]] = u;
}

int lca(int a, int b){
	if(level[a] < level[b]) swap(a, b);
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

vector<pair<pair<int, int>, pair<int, int>>> qry[SQRT2N];
bool has[N];
int freq[N], ans[M];

inline int check(int x){
	if(!has[x]){
		has[x] = true;
		if(++freq[weight[x]] == 1) return 1;
	}else{
		has[x] = false;
		if(--freq[weight[x]] == 0) return -1;
	}
	return 0;
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	vector<int> comp;
	for(int i = 1; i <= n; i++){
		scanf("%d", &weight[i]);
		comp.push_back(weight[i]);
	}
	sort(comp.begin(), comp.end());
	comp.resize(unique(comp.begin(), comp.end()) - comp.begin());
	for(int i = 1; i <= n; i++){
		weight[i] = lower_bound(comp.begin(), comp.end(), weight[i]) - comp.begin();
	}
	for(int i = 1; i < n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, 1, 0);
	for(int i = 0; i < m; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		if(ini[u] > ini[v]) swap(u, v);
		int anc = lca(u, v);
		if(anc == u) qry[ini[u]/SQRT2N].push_back({{ini[v], ini[u]}, {-1, i}});
		else qry[fin[u]/SQRT2N].push_back({{ini[v], fin[u]}, {anc, i}});
	}
	for(int i = 0; i < SQRT2N; i++){
		memset(freq, 0, sizeof(freq));
		memset(has, false, sizeof(has));
		sort(qry[i].begin(), qry[i].end());
		int nxt = (i + 1)*SQRT2N, cur_ans = 0;
		for(auto tmp : qry[i]){
			int l = tmp.first.second, r = tmp.first.first, pnt = tmp.second.first, qry_idx = tmp.second.second;
			
			while(nxt <= r) cur_ans += check(idx[nxt++]);
			
			int last = min(r, (i + 1)*SQRT2N - 1);
			
			for(int j = l; j <= last; j++) cur_ans += check(idx[j]);
			
			if(pnt != -1) cur_ans += check(pnt);
			
			ans[qry_idx] = cur_ans;
			
			if(pnt != -1) cur_ans += check(pnt);
			
			for(int j = l; j <= last; j++) cur_ans += check(idx[j]);
		}
	}
	for(int i = 0; i < m; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
