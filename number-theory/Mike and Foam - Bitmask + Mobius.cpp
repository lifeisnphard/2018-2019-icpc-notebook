/*
Mike is a bartender at Rico's bar. At Rico's, they put beer glasses in a special shelf. There are n kinds of beer at Rico's numbered from 1 to n. i-th kind of beer has ai milliliters of foam on it.

Maxim is Mike's boss. Today he told Mike to perform q queries. Initially the shelf is empty. In each request, Maxim gives him a number x. If beer number x is already in the shelf, then Mike should remove it from the shelf, otherwise he should put it in the shelf.

After each query, Mike should tell him the score of the shelf. Bears are geeks. So they think that the score of a shelf is the number of pairs (i, j) of glasses in the shelf such that i < j and  where  is the greatest common divisor of numbers a and b.
*/
#include <bits/stdc++.h>
#define len(o) ((int)(o).size())
#define get(o, i) get<i>(o)
#define x first
#define y second
using namespace std;

const int N = 2e5 + 10, A = 5e5 + 10;

int a[N], cnt[A], dp[A];
vector<int> p[A];
bool is[A];

long long add(int x, int val){
	long long ret = 0;
	for(int mask = 0; mask < (1 << len(p[x])); mask++){
		if(!mask) dp[0] = 1;
		else dp[mask] = dp[mask & (mask - 1)]*p[x][__builtin_ctz(mask)];
		
		int d = dp[mask];
		int mobius = (__builtin_popcount(mask) & 1)? -1 : 1;
		ret -= mobius*cnt[d]*1LL*(cnt[d] - 1)/2;
		cnt[d] += val;
		ret += mobius*cnt[d]*1LL*(cnt[d] - 1)/2;
	}
	return ret;
}

int main(){
	int n, q;
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	for(int i = 2; i < A; i++) if(p[i].empty()){
		for(int j = i; j < A; j += i){
			p[j].push_back(i);
		}
	}
	long long ans = 0;
	while(q--){
		int x;
		scanf("%d", &x);
		ans += add(a[x], is[x]? -1 : 1);
		is[x] ^= 1;
		printf("%lld\n", ans);
	}
	return 0;
}
