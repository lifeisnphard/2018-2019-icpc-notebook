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
int qtd[N];
int dp[2][N], cnt[N];

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
	int i = 0;
	dp[i][0] = 0;
	for(int j = 1; j <= n; j++){
		dp[i][j] = 1e9;
	}
	for(int val = 1; val <= n; val++) if(qtd[val]){ // O(sqrt(n))
		int many = qtd[val]; i ^= 1;
		
		for(int j = 0; j <= n; j++){
			dp[i][j] = dp[!i][j];
			cnt[j] = 0;
		}
		
		for(int j = val; j <= n; j++){
			if(dp[!i][j] < dp[i][j]){
				dp[i][j] = dp[!i][j - val];
				cnt[j] = 0;
			}
			if(dp[!i][j - val] + 1 < dp[i][j]){
				dp[i][j] = dp[!i][j - val] + 1;
				cnt[j] = 1;
			}
			if(cnt[j - val] < many && dp[i][j - val] + 1 < dp[i][j]){
				dp[i][j] = dp[i][j - val] + 1;
				cnt[j] = cnt[j - val] + 1;
			}
		}
	}
	int ans = 1e9;
	for(int j = 4; j <= n; j++){
		if(lucky(j)) ans = min(ans, dp[i][j]);
	}
	printf("%d\n", ans < 1e9 ? ans - 1 : -1);
	return 0;
}
