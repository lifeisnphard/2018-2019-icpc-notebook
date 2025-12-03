/*
Let's call an array a of size n coprime iff gcd(a1, a2, ..., an) = 1, where gcd is the greatest common divisor of the arguments.

You are given two numbers n and k. For each i (1 ≤ i ≤ k) you have to determine the number of coprime arrays a of size n such that for every j (1 ≤ j ≤ n) 1 ≤ aj ≤ i. Since the answers can be very large, you have to calculate them modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
#define len(o) ((int)(o).size())
#define get(o, i) get<i>(o)
#define x first
#define y second
using namespace std;

const int NK = 2e6 + 10, MOD = 1e9 + 7;

int powmod(int a, int x){
	if(x == 0) return 1;
	if(x%2 == 0) return powmod(a*1LL*a%MOD, x/2);
	return a*1LL*powmod(a, x - 1)%MOD;
}

int dp[NK];

int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= k; i++){
		dp[i] = powmod(i, n);
	}
	for(int i = k; i >= 2; i--){
		dp[i] = (dp[i] - dp[i - 1] + MOD)%MOD;
	}
	int sum = 0, ans = 0;
	for(int i = 1; i <= k; i++){
		for(int j = 2*i; j <= k; j += i){ // there will be dp[i] arrays where every element <= j and gcd(all) = j/i
			dp[j] = (dp[j] - dp[i] + MOD)%MOD;
		}
		sum = (sum + dp[i])%MOD;
		ans = (ans + (sum^i))%MOD;
	}
	printf("%d\n", ans);
	return 0;
}
