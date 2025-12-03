/*
Given a graph, calculate the minimum number of edges you must add such that the resulting graph has a component of lucky size. "Everybody knows that positive integers are lucky if their decimal representation doesn't contain digits other than 4 and 7."
*/
#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int N = 1e5 + 10;

int par[N], rnk[N], sz[N];
int qtd[N], dp[N], used[N];

int fnd(int u){
	if(par[u] == u) return u;
	return par[u] = fnd(par[u]);
}

void join(int a, int b){
	a = fnd(a), b = fnd(b);
	if(a != b){
		if(rnk[a] < rnk[b]) swap(a, b);
		else if(rnk[a] == rnk[b]) rnk[a]++;
		par[b] = a;
		sz[a] += sz[b];
	}
}

bool lucky(int num){
	while(num){
		int d = num%10;
		if(d != 4 && d != 7) return false;
		num /= 10;
	}
	return true;
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		par[i] = i, sz[i] = 1;
	}
	while(m--){
		int u, v;
		scanf("%d %d", &u, &v);
		join(u, v);
	}
	for(int i = 1; i <= n; i++){
		if(par[i] == i) qtd[sz[i]]++;
	}
	dp[0] = 0;
	for(int i = 1; i <= n; i++){
		dp[i] = 1e9;
	}
	for(int i = 1; i <= n; i++) if(qtd[i]){ // O(sqrt(n))
		int val = i, many = qtd[i];
		for(int j = 1; many; j = min(j << 1, many)){
			int jval = j*val;
			for(int k = n; k >= jval; k--){
				dp[k] = min(dp[k], dp[k - jval] + j);
			}
			many -= j;
		}
	}
	int ans = 1e9;
	for(int i = 4; i <= n; i++){
		if(lucky(i)) ans = min(ans, dp[i]);
	}
	printf("%d\n", ans < 1e9 ? ans - 1 : -1);
	return 0;
}
