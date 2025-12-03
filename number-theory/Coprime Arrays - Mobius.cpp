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

int m[NK], p[NK];
vector<int> dv[NK];

void sieve(int lim){
	m[1] = 1;
	vector<int> primes;
	vector<bool> composite(lim + 1);
	for(int i = 2; i <= lim; i++){
		if(!composite[i]){
			m[i] = -1;
			primes.push_back(i);
		}
		for(int p : primes){
			if(p*1LL*i > lim) break;
			composite[p*i] = true;
			if(i%p != 0) m[p*i] = -m[i];
			else break;
		}
	}
}

int powmod(int a, int x){
	if(x == 0) return 1;
	if(x%2 == 0) return powmod(a*1LL*a%MOD, x/2);
	return a*1LL*powmod(a, x - 1)%MOD;
}

int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	
	sieve(k);
	for(int i = 1; i <= k; i++){
		p[i] = powmod(i, n);
		for(int j = i; j <= k; j += i){
			dv[j].push_back(i);
		}
	}
	
	int sum = 0, ans = 0;
	for(int i = 1; i <= k; i++){
		for(int d : dv[i]){
			sum = (sum + m[d]*(p[i/d] - p[i/d - 1]))%MOD;
			if(sum < 0) sum += MOD;
		}
		ans = (ans + (sum^i))%MOD;
	}
	printf("%d\n", ans);
	return 0;
}
