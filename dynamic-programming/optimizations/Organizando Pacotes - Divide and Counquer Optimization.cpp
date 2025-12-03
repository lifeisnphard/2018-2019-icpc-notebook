/*
Uma empresa de mineração extrai térbio, um metal raro usado para a construção de ímãs leves, a partir de areia de rio. Eles mineram um grande rio em N pontos de mineração, cada um deles identificado por sua distância a partir da origem do rio. Em cada ponto de mineração, uma pequena pilha ou amontoado de minério mineral altamente valorizado é extraido do rio.

Para recolher o minério mineral, a empresa reagrupa os N amontoados produzidos em um menor número de K pilhas ou montes maiores, cada um localizado num dos pontos de extração inicial. Os montes recém-formados são então recolhidos por caminhões.

Para reagrupar os N montes eles usam uma barca, o que na prática pode levar qualquer quantidade de minério mineral por ser bem larga. A barcaça começa na origem do rio e somente pode viajar rio abaixo, de modo que o amontoado de mineral produzido em um ponto X de mineração pode ser levado para um ponto Y de mineração somente se Y > X. Cada monte é movimentado completamente para outro ponto de mineração, ou não se move. O custo de mover um monte com peso W a partir de um ponto X de mineração para um ponto Y de mineração é W (Y - X). O custo total do agrupamento é a soma dos custos de cada movimento de um monte. Nota-se que um monte que não é movido não tem influência sobre o custo total.

Divide and Conquer Optimization:
Recurrence: dp[i][j] = min_(k < j){dp[i - 1][k] + C[k][j]}
Condition: A[i][j] ≤ A[i][j + 1]	
Goes from O(k * n^2) to O(k * n * logn)
*/
#include <bits/stdc++.h>
using namespace std;

const int NK = 1010;

int n, k;
int x[NK], w[NK];
long long cost[NK][NK], dp[NK][NK];

void calc(int g, int l, int r, int optL, int optR){
    if(l <= r){
        int mid = (l + r)/2;

        int best = -1;
        for(int i = optL; i <= min(optR, mid - 1); i++){
            if(best == -1 || dp[g - 1][i] + cost[i + 1][mid] < dp[g - 1][best] + cost[best + 1][mid]){
                best = i;
            }
        }
        if(best == -1){
            dp[g][mid] = 1LL << 61;
        }else{
            dp[g][mid] = dp[g - 1][best] + cost[best + 1][mid];
        }
        calc(g, l, mid - 1, optL, best);
        calc(g, mid + 1, r, best, optR);
    }
}

int main(){
    while(scanf("%d %d", &n, &k) != EOF){
        for(int i = 1; i <= n; i++){
            scanf("%d %d", &x[i], &w[i]);
        }
        for(int r = 1; r <= n; r++){
            cost[r][r] = 0;
            for(int l = r - 1; l >= 1; l--){
                cost[l][r] = (x[r] - x[l])*1LL*w[l] + cost[l + 1][r];
            }
        }
        for(int i = 1; i <= n; i++){
            dp[1][i] = cost[1][i];
        }
        for(int i = 2; i <= k; i++){
            calc(i, 1, n, 1, n);
        }
        printf("%lld\n", dp[k][n]);
    }
    return 0;
}
