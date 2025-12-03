/*
On the way home, Karen decided to stop by the supermarket to buy some groceries.

She needs to buy a lot of goods, but since she is a student her budget is still quite limited. In fact, she can only spend up to b dollars.

The supermarket sells n goods. The i-th good can be bought for ci dollars. Of course, each good can only be bought once.

Lately, the supermarket has been trying to increase its business. Karen, being a loyal customer, was given n coupons. If Karen purchases the i-th good, she can use the i-th coupon to decrease its price by di. Of course, a coupon cannot be used without buying the corresponding good.

There is, however, a constraint with the coupons. For all i ≥ 2, in order to use the i-th coupon, Karen must also use the xi-th coupon (which may mean using even more coupons to satisfy the requirement for that coupon).

Karen wants to know the following. What is the maximum number of goods she can buy, without exceeding her budget b?
*/
#include <bits/stdc++.h>
#define len(o) ((int)(o).size())
#define get(o, i) get<i>(o)
#define x first
#define y second
using namespace std;

const int N = 5010;

int n, b;
int c[N], d[N], qtd[N];
vector<int> adj[N];
long long dp[N][N][2];

void dfs(int u){
	for(int i = 0; i <= n; i++)
		dp[u][i][0] = dp[u][i][1] = 1e18;
	
	dp[u][0][0] = dp[u][0][1] = 0;
	dp[u][1][0] = c[u];
	
	qtd[u] = 1;
	for(int v : adj[u]){
		dfs(v);
		qtd[u] += qtd[v];
		for(int i = qtd[u]; i >= 1; i--){
			for(int j = min(i, qtd[v]); j >= i + qtd[v] - qtd[u] && j >= 1; j--){
				dp[u][i][0] = min(dp[u][i][0], dp[u][i - j][0] + dp[v][j][0]);
				dp[u][i][1] = min(dp[u][i][1], dp[u][i - j][1] + dp[v][j][1]);
			}
		}
	}
	for(int i = qtd[u]; i >= 1; i--)
		dp[u][i][1] = min(dp[u][i][0], dp[u][i - 1][1] + c[u] - d[u]);
}

int main(){
	scanf("%d %d", &n, &b);
	for(int i = 1; i <= n; i++){
		scanf("%d %d", &c[i], &d[i]);
		if(i > 1){
			int p;
			scanf("%d", &p);
			adj[p].push_back(i);
		}
	}
	dfs(1);
	for(int i = n; i >= 0; i--){
		if(dp[1][i][1] <= b){
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}
