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

int a[N];
int cnt[A], mobius[A];

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

bool is[A];
vector<int> dv[A];

int main(){
	int n, q;
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	for(int i = 1; i < A; i++){
		for(int j = i; j < A; j += i){
			dv[j].push_back(i);
		}
	}
	sieve(A - 1);
	long long ans = 0;
	while(q--){
		int x;
		scanf("%d", &x);
		for(int d : dv[a[x]]){
			ans -= mobius[d]*cnt[d]*1LL*(cnt[d] - 1)/2;
			if(!is[x]) cnt[d]++;
			else cnt[d]--;
			ans += mobius[d]*cnt[d]*1LL*(cnt[d] - 1)/2;
		}
		is[x] ^= 1;
		printf("%lld\n", ans);
	}
	return 0;
}
