#include <bits/stdc++.h>
using namespace std;
#define len(x) ((int)(x).size())

const int N = 5e4 + 10;

int last[N/2];
vector<int> adj[N], qry[N];
int par[N], rnk[N], lowest[N];
bool out[N];
int level[N], ans;

int fnd(int u){
    if(par[u] == u) return u;
    return par[u] = fnd(par[u]);
}

int join(int a, int b){
    a = fnd(a), b = fnd(b);
    if(a != b){
        if(rnk[a] < rnk[b]) swap(a, b);
        else if(rnk[a] == rnk[b]) rnk[a]++;
        par[b] = a;
    }
    return a;
}

void dfs(int u, int p, int l = 0){
    level[u] = l;
    for(int v : adj[u]) if(v != p){
        dfs(v, u, l + 1);
        lowest[join(u, v)] = u;
    }
    out[u] = true;
    for(int x : qry[u]) if(out[x]){
        ans += level[x] + level[u] - 2*level[lowest[fnd(x)]];
    }
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
	    int c;
	    scanf("%d", &c);
	    if(last[c]){
	        qry[last[c]].push_back(i);
	        qry[i].push_back(last[c]);
	    }
	    last[c] = i;
	    par[i] = i;
	    rnk[i] = 1;
	}
	for(int i = 1; i < n; i++){
	    int a, b;
	    scanf("%d %d", &a, &b);
	    adj[a].push_back(b);
	    adj[b].push_back(a);
	}
	dfs(1, 1);
	printf("%d\n", ans);
	return 0;
}
