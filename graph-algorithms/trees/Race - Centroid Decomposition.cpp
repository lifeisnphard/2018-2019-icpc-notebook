/*
In the Pattaya-Chonburi metropolitan area, there are N cities connected by a network of N-1 highways. Each highway is bidirectional, connects two different cities, and has an integer length in kilometers. Furthermore, there is exactly one possible path connecting any pair of cities. That is, there is exactly one way to travel from one city to another city by a sequence of highways without visiting any city twice.
...
Your program must output the minimum number of highways on a valid race course of length exactly K. If there is no such course, your program must output -1.
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10, K = 1e6 + 10;

int n, k, sz[N];
vector<pair<int, int>> adj[N];
bool deleted[N];
int best[K];

void calc_sz(int u, int p){
	sz[u] = 1;
	for(auto edge : adj[u]){
		int v = edge.first;
		if(v != p && !deleted[v]){
			calc_sz(v, u);
			sz[u] += sz[v];
		}
	}
}

int find_centroid(int u, int p, int total){
	for(auto edge : adj[u]){
		int v = edge.first;
		if(v != p && !deleted[v] && 2*sz[v] > total){
			return find_centroid(v, u, total);
		}
	}
	return u;
}

int calc(int u, int p, int len, int sum){
	int ret = 1e9;
	if(sum <= k){
		ret = min(ret, len + best[k - sum]);
		for(auto edge : adj[u]){
			int v = edge.first, cost = edge.second;
			if(v != p && !deleted[v]){
				ret = min(ret, calc(v, u, len + 1, sum + cost));
			}
		}
	}
	return ret;
}

void add_all(int u, int p, int len, int sum){
	if(sum <= k){
		best[sum] = min(best[sum], len);
		for(auto edge : adj[u]){
			int v = edge.first, cost = edge.second;
			if(v != p && !deleted[v]){
				add_all(v, u, len + 1, sum + cost);
			}
		}
	}
}

void rmv_all(int u, int p, int sum){
	if(sum <= k){
		best[sum] = sum? 1e9 : 0;
		for(auto edge : adj[u]){
			int v = edge.first, cost = edge.second;
			if(v != p && !deleted[v]){
				rmv_all(v, u, sum + cost);
			}
		}
	}
}

int solve(int u){
	calc_sz(u, u);
	u = find_centroid(u, u, sz[u]);
	
	int ret = 1e9;
	for(auto edge : adj[u]){
		int v = edge.first, cost = edge.second;
		if(!deleted[v]){
			ret = min(ret, calc(v, u, 1, cost));
			add_all(v, u, 1, cost);
		}
	}
	
	for(auto edge : adj[u]){
		int v = edge.first, cost = edge.second;
		if(!deleted[v]){
			rmv_all(v, u, cost);
		}
	}
	
	deleted[u] = true;
	for(auto edge : adj[u]){
		int v = edge.first;
		if(!deleted[v]){
			ret = min(ret, solve(v));
		}
	}
	return ret;
}

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 1; i < n; i++){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
	}
	for(int i = 1; i <= k; i++){
		best[i] = 1e9;
	}
	int ans = solve(1);
	printf("%d\n", (ans < 1e9)? ans : -1);
	return 0;
}
