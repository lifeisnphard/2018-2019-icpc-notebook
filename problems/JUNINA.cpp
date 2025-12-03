/*
Questão: Festa Junina
Assunto: Encontrar o maior subconjunto de vértices independentes em um grafo (NP-completo)
Resposta: Accepted
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
 
using namespace std;
 
int adj[20];
bool dp[1<<20];
 
int solve(int n){
    int res = 0;
    dp[0] = true;
    for(int mask = 1; mask < (1<<n); mask++){
        int i = __builtin_ctz(mask);
        dp[mask] = !(mask&adj[i]) and dp[mask&(~(1<<i))];
        if(dp[mask])
            res = max(res,__builtin_popcount(mask));
    }
    return res;
}
 
int main(){
    int n, x, caso = 0;
 
    while(scanf("%d", &n), n!=0){
        memset(adj,0,sizeof(adj));
        memset(dp,false,sizeof(dp));
        for(int i = 0; i < n; i++) while(scanf("%d", &x), x!=0){
            x--;
            adj[i] |= (1<<x);
            adj[x] |= (1<<i);
        }
        printf("Teste %d\n", ++caso);
        printf("%d\n\n", solve(n));
    }
 
    return 0;
}
