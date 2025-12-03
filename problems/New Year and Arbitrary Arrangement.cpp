/*
You are given three integers k, pa and pb.

You will construct a sequence with the following algorithm: Initially, start with the empty sequence. Each second, you do the following. With probability pa / (pa + pb), add 'a' to the end of the sequence. Otherwise (with probability pb / (pa + pb)), add 'b' to the end of the sequence.

You stop once there are at least k subsequences that form 'ab'. Determine the expected number of times 'ab' is a subsequence in the resulting sequence. It can be shown that this can be represented by P / Q, where P and Q are coprime integers, and Q != 0 mod (10^9 + 7). Print the value of P * Q^-1 mod (10^9 + 7).

-

Mauricio's explanation about the formula:

[18:14, 29/12/2017] Maurício: Imagina que você tem mais de k A e nenhum B, primeiro
[18:15, 29/12/2017] Maurício: Digo, tem exatamente k As e nenhum B
[18:15, 29/12/2017] Maurício: Qual o número esperado de subsequências?
[18:15, 29/12/2017] Maurício: Bom, chamemos esse número de X
[18:16, 29/12/2017] Maurício: Seja p a probabilidade de sair um B
[18:16, 29/12/2017] Maurício: Com probabilidade p, você coloca um B e tem exatamente K subsequencias
[18:17, 29/12/2017] Maurício: Com probabilidade 1-p, você coloca um A e cai na mesma situação, exceto que quando o B finalmente sair você vai ter uma subsequência a mais
[18:17, 29/12/2017] Maurício: Então X = p*K + (1-p)(1+X)
[18:17, 29/12/2017] Maurício: Se você resolver para X, obtém o valor esperado
[18:18, 29/12/2017] Maurício: X - (1-p)X = p*K + 1-p => X = K + (1-p)/p
[18:18, 29/12/2017] Maurício: (Ou K-1 + 1/p, se preferir)
[18:18, 29/12/2017] Maurício: Esse é o caso em que você começou com zero subsequências
[18:19, 29/12/2017] Maurício: Não sei se faz sentido
[18:19, 29/12/2017] Maurício: Pode perguntar se quiser algum esclarecimento

General case when I already have Y done subsequences:

[18:55, 29/12/2017] Maurício: Com probabilidade p, você termina com K + Y
[18:55, 29/12/2017] Maurício: Com probabilidade 1-p, você cai no caso anterior com 1 sequencia a mais
[18:56, 29/12/2017] Maurício: Então fica X = p*(Y+K) + (1-p)(1+X)
[18:56, 29/12/2017] Maurício: Que dá X = Y + K-1 + 1/p
[18:56, 29/12/2017] Maurício: (Ou seja, basta somar o Y na resposta final anterior)
*/
#include <bits/stdc++.h>

using namespace std;

#define len(x) ((int)(x).size())
#define x first
#define y second

using ll = long long;
using llu = unsigned long long;
using ld = long double;

const int K = 1010, MOD = 1e9 + 7;

int modpow(int a, int x){
	int ret = 1;
	while(x){
		if(x & 1) ret = ret*1LL*a%MOD;
		a = a*1LL*a%MOD, x >>= 1;
	}
	return ret;
}

int inv(int x){
	return modpow(x, MOD - 2);
}

int k, pa, pb;
int p, one_p, val;
int dp[K][K];

int solve(int subs = 0, int qtdA = 1){
	if(subs >= k) return subs;
	if(qtdA >= k) return (1LL*subs + qtdA + val)%MOD;
	
	int &ret = dp[subs][qtdA];
	if(ret == -1){
		ret = 0;
		ret = (ret + p*1LL*solve(subs, qtdA + 1))%MOD;
		ret = (ret + one_p*1LL*solve(subs + qtdA, qtdA))%MOD;
	}
	return ret;
}

int main(){
	scanf("%d %d %d", &k, &pa, &pb);
	
	int inv_den = inv((pa + pb)%MOD);
	
	p = pa*1LL*inv_den%MOD;
	one_p = pb*1LL*inv_den%MOD;
	val = p*1LL*inv(one_p)%MOD;
	
	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve());
	
	return 0;
}
