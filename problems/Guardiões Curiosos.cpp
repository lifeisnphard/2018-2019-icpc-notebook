/*
Existem N cidades em Oa, e eles desejam construir N−1 estradas de duas mãos, de tal forma que seja possível chegar de uma cidade até qualquer outra, direta ou indiretamente. Os guardiões também não desejam privilegiar demais nenhuma cidade, por isso eles estabeleceram que nenhuma cidade pode ter mais de K estradas.

Os guardiões, porém, são muito curiosos, e perguntaram aos lanternas verdes se eles eram capazes de dizer de quantas formas é possível construir N−1 estradas obedecendo estas restrições. Sua tarefa, como membro da tropa dos lanternas verdes é, dados N e K, satisfazer a curiosidade dos guardiões.

N <= 10^2, K <= N
*/
#include <bits/stdc++.h>
using namespace std;
#define len(x) ((int)(x).size())

const int NK = 110, MOD = 1e9 + 7;

int n, k_max;
int comb[NK][NK], dp[NK][NK];

int solve(int n, int k){
	if(n == 1) return 1;
	if(k == 0) return 0;
	int &ret = dp[n][k];
	if(ret == -1){
		ret = 0;
		for(int i = 1; i < n; i++){
			int cur = comb[n - 2][i - 1];
			cur = (cur*1LL*i)%MOD;
			cur = (cur*1LL*solve(i, k_max - 1))%MOD;
			cur = (cur*1LL*solve(n - i, k - 1))%MOD;
			ret = (ret + cur)%MOD;
		}
	}
	return ret;
}

int main(){
	scanf("%d %d", &n, &k_max);
	for(int i = 0; i <= n; i++){
		comb[i][0] = 1;
		for(int j = 1; j <= i; j++){
			comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j])%MOD;
		}
	}
	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(n, k_max));
	return 0;
}
