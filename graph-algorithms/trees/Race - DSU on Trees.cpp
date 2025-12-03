/*
In the Pattaya-Chonburi metropolitan area, there are N cities connected by a network of N-1 highways. Each highway is bidirectional, connects two different cities, and has an integer length in kilometers. Furthermore, there is exactly one possible path connecting any pair of cities. That is, there is exactly one way to travel from one city to another city by a sequence of highways without visiting any city twice.
...
Your program must output the minimum number of highways on a valid race course of length exactly K. If there is no such course, your program must output -1.
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10, K = 1e6 + 10;

int n, k;
vector<pair<int, int>> adj[N];
int sz[N], sc[N], se[N];
unordered_map<long long, int> best;

void dfs(int u, int p){
    sz[u] = 1, sc[u] = -1;
    for(auto tmp : adj[u]){
        int v = tmp.first, cost = tmp.second;
        if(v != p){
            dfs(v, u);
            sz[u] += sz[v];
            if(sc[u] == -1 || sz[v] > sz[sc[u]]) sc[u] = v, se[u] = cost;
        }
    }
}

void add(long long sum, int len){
    if(!best.count(sum)) best[sum] = len;
    else best[sum] = min(best[sum], len);
}

void add_all(int u, int p, int len, long long sum){
    add(sum, len);
    for(auto tmp : adj[u]){
        int v = tmp.first, cost = tmp.second;
        if(v != p) add_all(v, u, len + 1, sum + cost);
    }
}

void rmv_all(int u, int p, int len, long long sum){
    best.erase(sum);
    for(auto tmp : adj[u]){
        int v = tmp.first, cost = tmp.second;
        if(v != p) rmv_all(v, u, len + 1, sum + cost);
    }
}

int calc(int u, int p, int len, long long sum, int plen, long long psum){
    int ret = 1e9;
    if(best.count(k + 2*psum - sum)){
        ret = best[k + 2*psum - sum] + len - 2*plen;
    }
    for(auto tmp : adj[u]){
        int v = tmp.first, cost = tmp.second;
        if(v != p) ret = min(ret, calc(v, u, len + 1, sum + cost, plen, psum));
    }
    return ret;
}

int solve(int u, int p, int len = 0, long long sum = 0){
    int ret = 1e9;
    if(sc[u] != -1){
        for(auto tmp : adj[u]){
            int v = tmp.first, cost = tmp.second;
            if(v != p && v != sc[u]){
                ret = min(ret, solve(v, u, len + 1, sum + cost));
                rmv_all(v, u, len + 1, sum + cost);
            }
        }
        ret = min(ret, solve(sc[u], u, len + 1, sum + se[u]));
    }
    
    if(best.count(sum + k)){
        ret = min(ret, best[sum + k] - len);
    }
    
    add(sum, len);
    
    for(auto tmp : adj[u]){
        int v = tmp.first, cost = tmp.second;
        if(v != p && v != sc[u]){
            ret = min(ret, calc(v, u, len + 1, sum + cost, len, sum));
            add_all(v, u, len + 1, sum + cost);
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
	dfs(0, 0);
	int ans = solve(0, 0);
	printf("%d\n", (ans < 1e9)? ans : -1);
	return 0;
}
