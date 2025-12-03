/*
Devu wants to decorate his garden with flowers. He has purchased n boxes, where the i-th box contains fi flowers. All flowers in a single box are of the same color (hence they are indistinguishable). Also, no two boxes have flowers of the same color.

Now Devu wants to select exactly s flowers from the boxes to decorate his garden. Devu would like to know, in how many different ways can he select the flowers from each box? Since this number may be very large, he asks you to find the number modulo (109 + 7).

Devu considers two ways different if there is at least one box from which different number of flowers are selected in these two ways.
n <= 20, s <= 10^14, f_i <= 10^12
*/
#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
#define x first
#define y second
using namespace std;

const int N = 25, MOD = 1e9 + 7;

long long f[N];

int powmod(int a, int x){
	int ret = 1;
	for(; x; x >>= 1){
		if(x & 1) ret = ret*1LL*a%MOD;
		a = a*1LL*a%MOD;
	}
	return ret;
}

int choose(long long n, int p){
	int fact = 1;
	for(int i = 2; i <= p; i++){
		fact = fact*1LL*i%MOD;
	}
	int ret = powmod(fact, MOD - 2);
	for(int i = 0; i < p; i++){
		int mult = ((n - i)%MOD + MOD)%MOD;
		ret = ret*1LL*mult%MOD;
	}
	return ret;
}

int main(){
	int n; long long s;
	scanf("%d %lld", &n, &s);
	for(int i = 0; i < n; i++){
		scanf("%lld", &f[i]);
	}
	int ans = 0;
	for(int mask = 0; mask < (1 << n); mask++){
		long long sum = 0;
		for(int i = 0; i < n; i++) if(mask & (1 << i)){
			sum += f[i] + 1;
		}
		if(sum <= s){
			int add = choose(s - sum + n - 1, n - 1);
			if(__builtin_popcount(mask) & 1) add = -add;
			ans = ((ans + add)%MOD + MOD)%MOD;
		}
	}
	printf("%d\n", ans);
	return 0;
}
