/*
Sorteando dois números inteiros A e B entre 1 e N inclusive, qual é a chance de que o número B seja menor ou igual ao resto de N dividido por A?

Por exemplo, para N=5, há 25 escolhas possíveis para (A,B), porém os únicos pares que satisfazem o enunciado são (2,1), (3,1), (3,2) e (4,1). Portanto para N=5, a probabilidade é igual a 4/25.
-
Resumindo: encontrar fração irredutível num/(n*n), onde num = sum_{1 <= i <= n} (n mod i)
*/
#include <stdio.h>
#include <algorithm>

using ll = long long;

ll gcd(ll a, ll b){
	while(b) a %= b, std::swap(a, b);
	return a;
}

int main(){
	int n;
	while(scanf("%d", &n) != EOF){
		ll sum = 0;
		
		for(int l = 1, r; l <= n; l = r + 1){
			int f = n/l;
			r = n/f;
			
			int a1 = n - l*f, an = n - r*f;
			sum += (a1 + an)*1LL*(r - l + 1)/2;
		}
		
		ll tot = n*1LL*n;
		ll d = gcd(sum, tot);
		sum /= d, tot /= d;
		
		printf("%lld/%lld\n", sum, tot);
	}
	return 0;
}