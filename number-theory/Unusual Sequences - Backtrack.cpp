/*
Count the number of distinct sequences a1, a2, ..., an (1 ≤ ai) consisting of positive integers such that gcd(a1, a2, ..., an) = x and sum(a_i) = y. As this number could be large, print the answer modulo 10^9 + 7.
*/
#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
#define x first
#define y second
using namespace std;

const int MOD = 1e9 + 7;

int powmod(int a, int x){
	int ret = 1;
	for(; x; x >>= 1){
		if(x & 1) ret = ret*1LL*a%MOD;
		a = a*1LL*a%MOD;
	}
	return ret;
}

unordered_map<int, int> mp;

int solve(int y){
	if(y == 1) return 1;
	if(mp.count(y)) return mp[y];
	int ret = powmod(2, y - 1) - 1;
	for(int i = 2; i*i <= y; i++) if(y%i == 0){
		ret = (ret - solve(y/i) + MOD)%MOD;
		if(y/i != i){
			ret = (ret - solve(i) + MOD)%MOD;
		}
	}
	return mp[y] = ret;
}

int main(){
	int x, y;
	scanf("%d %d", &x, &y);
	if(y%x != 0){
		printf("0\n");
	}else{
		printf("%d\n", solve(y/x));
	}
	return 0;
}
