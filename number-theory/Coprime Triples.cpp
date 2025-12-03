/*
You are given a sequence a1, a2, ..., aN. Count the number of triples (i, j, k) such that 1 ≤ i < j < k ≤ N and GCD(ai, aj, ak) = 1. Here GCD stands for the Greatest Common Divisor.

N <= 1e5, a_i <= 1e6
*/
#include <bits/stdc++.h>
#define len(o) ((int)(o).size())
#define get(o, i) get<i>(o)
#define x first
#define y second
using namespace std;

const int A = 1e6 + 10;

int cnt[A], dp[A], mobius[A];

void sieve(int lim){
	mobius[1] = 1;
	vector<int> primes;
	vector<bool> composite(lim + 1);
	for(int i = 2; i <= lim; i++){
		if(!composite[i]){
			primes.push_back(i);
			mobius[i] = -1;
		}
		for(int p : primes){
			if(p*1LL*i > lim) break;
			composite[p*i] = true;
			if(i%p == 0) break;
			mobius[p*i] = -mobius[i];
		}
	}
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int a;
		scanf("%d", &a);
		cnt[a]++;
	}
	for(int i = 1; i < A; i++){
		for(int j = i; j < A; j += i){
			dp[i] += cnt[j];
		}
	}
	sieve(A - 1);
	long long ans = 0;
	for(int i = 1; i < A; i++){
		long long g = dp[i]*1LL*(dp[i] - 1)*(dp[i] - 2)/6;
		ans += mobius[i]*g;
	}
	printf("%lld\n", ans);
	return 0;
}
