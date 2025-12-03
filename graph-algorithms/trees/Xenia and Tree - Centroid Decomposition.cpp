/*
Xenia the programmer has a tree consisting of n nodes. We will consider the tree nodes indexed from 1 to n. We will also consider the first node to be initially painted red, and the other nodes — to be painted blue.

The distance between two tree nodes v and u is the number of edges in the shortest path between v and u.

Xenia needs to learn how to quickly execute queries of two types:

1. paint a specified blue node in red;
2. calculate which red node is the closest to the given one and print the shortest distance to the closest red node.

Your task is to write a program which will execute the described queries.
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, LOGN = 18;

vector<int> adj[N];
int parent[N][LOGN], level[N];

void dfs(int u, int p){
	parent[u][0] = p;
	for(int k = 1; k < LOGN; k++){
		parent[u][k] = parent[parent[u][k - 1]][k - 1];
	}
	for(int v : adj[u]) if(v != p){
		level[v] = level[u] + 1;
		dfs(v, u);
	}
}

int lca(int a, int b){
	if(level[a] < level[b]){
		swap(a, b);
	}
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

inline int dist(int a, int b){
	return level[a] + level[b] - 2*level[lca(a, b)];
}

int sz[N];
bool blocked[N];

void calc_sz(int u, int p){
	sz[u] = 1;
	for(int v : adj[u]) if(v != p && !blocked[v]){
		calc_sz(v, u);
		sz[u] += sz[v];
	}
}

int find_centroid(int u, int p, int tot){
	for(int v : adj[u]) if(v != p && !blocked[v]){
		if(2*sz[v] > tot) return find_centroid(v, u, tot);
	}
	return u;
}

int ct_parent[N];

void divide_and_conquer(int u, int prev){
	calc_sz(u, u);
	u = find_centroid(u, u, sz[u]);
	ct_parent[u] = prev;
	blocked[u] = true;
	for(int v : adj[u]) if(!blocked[v]){
		divide_and_conquer(v, u);
	}
}

bool white[N];
multiset<int> ms[N];

void add(int ct_anc, int u){
	if(ct_anc == -1) return;
	ms[ct_anc].insert(dist(u, ct_anc));
	add(ct_parent[ct_anc], u);
}

void rmv(int ct_anc, int u){
	if(ct_anc == -1) return;
	ms[ct_anc].erase(ms[ct_anc].find(dist(u, ct_anc)));
	rmv(ct_parent[ct_anc], u);
}

int solve(int ct_anc, int u){
	if(ct_anc == -1) return 1e9;
	int ret = solve(ct_parent[ct_anc], u);
	if(!ms[ct_anc].empty()) ret = min(ret, dist(u, ct_anc) + *ms[ct_anc].begin());
	return ret;
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 1; i < n; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1, 1);
	divide_and_conquer(1, -1);
	white[1] = true;
	add(1, 1);
	while(m--){
		int t, u;
		scanf("%d %d", &t, &u);
		if(t == 1){
			if(!white[u]){
				white[u] = true;
				add(u, u);
			}else{
				white[u] = false;
				rmv(u, u);
			}
		}else{
			int go = solve(u, u);
			printf("%d\n", (go < 1e9)? go : -1);
		}
	}
	return 0;
}
