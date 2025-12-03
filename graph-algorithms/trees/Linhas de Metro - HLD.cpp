/*
Given a tree answer several queries of the form: find the number of vertices that appears at the same time in two given paths.
*/
#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
using namespace std;

const int N = 1e5 + 10;

int L[N], R[N];

inline void pre(){
	memset(L, 0, sizeof(L));
	memset(R, -1, sizeof(R));
}

inline void add(int chain_idx, int l, int r, int val){
	if(val == -1) l = 0, r = -1;
	L[chain_idx] = l, R[chain_idx] = r;
}

inline int query(int chain_idx, int l, int r){
	return max(0, min(r, R[chain_idx]) - max(l, L[chain_idx]) + 1);
}

int n, q;
vector<int> g[N];
int par[N], sz[N], sc[N], chain[N], in[N], euler_cnt;

void dfs(int u, int p){
	par[u] = p;
	sz[u] = 1, sc[u] = -1;
	for(int v : g[u]) if(v != p){
		dfs(v, u);
		sz[u] += sz[v];
		if(sc[u] == -1 || sz[v] > sz[sc[u]]){
			sc[u] = v;
		}
	}
}

void dfs_hld(int u){
	in[u] = ++euler_cnt;
	if(!chain[u]) chain[u] = u;
	
	if(sc[u] != -1){
		chain[sc[u]] = chain[u];
		dfs_hld(sc[u]);
		
		for(int v : g[u]) if(v != par[u] && v != sc[u]){
			dfs_hld(v);
		}
	}
}

void hld_upd(int a, int b, int val){
	if(chain[a] == chain[b]){
		if(in[a] > in[b]) swap(a, b);
		add(chain[a], in[a], in[b], val);
		return;
	}
	if(in[chain[a]] < in[chain[b]]) swap(a, b);
	add(chain[a], in[chain[a]], in[a], val);
	return hld_upd(par[chain[a]], b, val);
}

int hld_query(int a, int b){
	if(chain[a] == chain[b]){
		if(in[a] > in[b]) swap(a, b);
		return query(chain[a], in[a], in[b]);
	}
	if(in[chain[a]] < in[chain[b]]) swap(a, b);
	return query(chain[a], in[chain[a]], in[a]) + hld_query(par[chain[a]], b);
}

int main(){
	pre();
	
	scanf("%d %d", &n, &q);
	for(int i = 1; i < n; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1, 1);
	dfs_hld(1);
	
	for(int i = 0; i < q; i++){
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		hld_upd(a, b, 1);
		printf("%d\n", hld_query(c, d));
		hld_upd(a, b, -1);
	}
	
	return 0;
}