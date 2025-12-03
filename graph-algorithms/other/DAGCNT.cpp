/*
"In graph theory, an arborescence is a directed graph in which, for a vertex v called the root and any other vertex u, there is exactly one directed path from v to u. In other words, an arborescence is a directed, rooted tree in which all edges point away from the root. Every arborescence is a directed acyclic graph."

-- from Wikipedia, the free encyclopedia

You are given a directed graph with N vertices, and your task is to count the number of different arborescences of size N that can be found in the given graph.

Two arborescences are considered different when they consist of different edges.
*/
#include <bits/stdc++.h>
using namespace std;
 
const int N = 10;
 
int n, adj[N];
long long dp[N][(1 << 8) + 10];
 
long long solve(int u, int mask){
    if(mask == 0) return 1;
    long long &ret = dp[u][mask];
    if(ret == -1){
        ret = 0;
        int nxt = __builtin_ctz(mask); mask ^= (1 << nxt);
        for(int submask = mask; ; submask = (submask - 1) & mask){
            for(int aux = (submask | (1 << nxt)) & adj[u]; aux; aux &= (aux - 1)){
				int v = __builtin_ctz(aux);
				assert((adj[u] & (1 << v)) && ((submask | (1 << nxt)) & (1 << v)));
				ret += solve(v, (submask | (1 << nxt)) ^ (1 << v)) * solve(u, mask ^ submask);
			}
			if(!submask) break;
        }
    }
    return ret;
}
 
int main(){
    while(scanf("%d", &n)){
        if(!n) break;
        for(int i = 0; i < n; i++){
            adj[i] = 0;
            for(int j = 0; j < n; j++){
				int x;
                scanf("%1d", &x);
                adj[i] |= x*(1 << j);
            }
        }
        long long ans = 0;
        memset(dp, -1, sizeof(dp));
        for(int i = 0; i < n; i++){
            ans += solve(i, ((1 << n) - 1) ^ (1 << i));
        }
        printf("%lld\n", ans);
    }
    return 0;
}
