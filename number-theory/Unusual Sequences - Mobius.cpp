/*
Count the number of distinct sequences a1, a2, ..., an (1 ≤ ai) consisting of positive integers such that gcd(a1, a2, ..., an) = x and sum(a_i) = y. As this number could be large, print the answer modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
#define x first
#define y second
using namespace std;

const int MOD = 1e9 + 7;

vector<int> primes;

void sieve(int lim){
	vector<bool> composite(lim + 1);
	for(int i = 2; i <= lim; i++) if(!composite[i]){
		primes.push_back(i);
		for(int j = i*i; j <= lim; j += i) composite[j] = true;
	}
}

int mobius(int n){
	int ret = 1;
	for(int p : primes){
		if(p*1LL*p > n) break;
		if(n%p != 0) continue;
		if(n%(p*1LL*p) == 0) return 0;
		n /= p, ret = -ret;
	}
	if(n > 1) ret = -ret;
	return (ret + MOD)%MOD;
}

int powmod(int a, int x){
	if(x == 0) return 1;
	if(x%2 == 0) return powmod(a*1LL*a%MOD, x/2);
	return a*1LL*powmod(a, x - 1)%MOD;
}

int main(){
	int x, y, ans = 0;
	scanf("%d %d", &x, &y);
	if(y%x == 0){
		y /= x;
		vector<int> dv;
		for(int i = 1; i*i <= y; i++) if(y%i == 0){
			dv.push_back(i);
			if(y/i != i) dv.push_back(y/i);
		}
		sieve(sqrt(y));
		for(int d : dv){
			ans = (ans + mobius(d)*1LL*powmod(2, y/d - 1))%MOD;
		}
	}
	printf("%d\n", ans);
	return 0;
}
