/*
You are given a tree with N nodes. The tree nodes are numbered from 1 to N. Each node has an integer weight.

We will ask you to perform the following operation:

u v k : ask for the kth minimum weight on the path from node u to node v
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, LOGN = 18, PERS = 4*N + N*LOGN;

int n, weight[N], orig[N];
vector<int> adj[N];
int parent[N][LOGN], level[N];
int root[N], seg[PERS], L[PERS], R[PERS], seg_cnt;

int build(int l, int r){
	int idx = seg_cnt++;
	if(l != r){
		int mid = (l + r)/2;
		L[idx] = build(l, mid);
		R[idx] = build(mid + 1, r);
	}
	return idx;
}

int add(int idx, int l, int r, int pos){
	int nidx = seg_cnt++;
	if(l == r){
		seg[nidx] = seg[idx] + 1;
	}else{
		int mid = (l + r)/2;
		if(pos <= mid){
			L[nidx] = add(L[idx], l, mid, pos);
			R[nidx] = R[idx];
		}else{
			L[nidx] = L[idx];
			R[nidx] = add(R[idx], mid + 1, r, pos);
		}
		seg[nidx] = seg[L[nidx]] + seg[R[nidx]];
	}
	return nidx;
}

void dfs(int u, int p, int l){
	parent[u][0] = p;
	for(int k = 1; k < LOGN; k++){
		parent[u][k] = parent[parent[u][k - 1]][k - 1];
	}
	level[u] = l;
	root[u] = add(root[p], 1, n, weight[u]);
	for(int v : adj[u]) if(v != p){
		dfs(v, u, l + 1);
	}
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

int query(int pp, int p, int a, int b, int l, int r, int k){
	if(l == r) return l;
	int qtd_left = seg[L[a]] + seg[L[b]] - seg[L[p]] - seg[L[pp]], mid = (l + r)/2;
	if(qtd_left >= k) return query(L[pp], L[p], L[a], L[b], l, mid, k);
	return query(R[pp], R[p], R[a], R[b], mid + 1, r, k - qtd_left);
}

int main(){
	int m;
	scanf("%d %d", &n, &m);
	vector<int> comp;
	for(int i = 1; i <= n; i++){
		scanf("%d", &weight[i]);
		comp.push_back(weight[i]);
	}
	sort(comp.begin(), comp.end());
	comp.resize(unique(comp.begin(), comp.end()) - comp.begin());
	for(int i = 1; i <= n; i++){
		int nxt = lower_bound(comp.begin(), comp.end(), weight[i]) - comp.begin() + 1;
		orig[nxt] = weight[i];
		weight[i] = nxt;
	}
	for(int i = 1; i < n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	root[0] = build(1, n);
	dfs(1, 0, 0);
	while(m--){
		int u, v, k;
		scanf("%d %d %d", &u, &v, &k);
		int p = lca(u, v), pp = parent[p][0];
		printf("%d\n", orig[query(root[pp], root[p], root[u], root[v], 1, n, k)]);
	}
	return 0;
}
