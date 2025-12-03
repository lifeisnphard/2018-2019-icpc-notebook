/*
Para quaquer inteiro N, um inteiro positivo A só é considerado H-Number em relação a N se e somente se:

- MMC(N,A) = N * A

MMC é o Minimo Multiplo Comum entre dois números.

Ex1: N = 20, H-Números = {1,3,7,9,11,13,17,19}

Ex2: N = 10, H-Números = {1,3,7,9}

Para resolver este problema, ele precisa saber para um dado inteiro N o numero de H-Números de N que estão dentro do intervalo [1,M], inclusivo.
*/
#include <bits/stdc++.h>
using namespace std;
 
int fatores[320];
 
int main(){
    int q;
    scanf("%d", &q);
    while(q--){
        int n, m;
        scanf("%d %d", &n, &m);
        int cnt = 0;
        // Para fatorar um número N, basta usar os números primos menores ou iguais sqrt(N)
        for(int i = 2; n > 1 && i*i <= n; i++){
            // Se houver fatores i em N, adicione no vetor
            if(n%i == 0) fatores[cnt++] = i;
            // Retire todos os fatores i em N
            while(n%i == 0) n /= i;
        }
        // Se N ainda nÃ£o foi completamente fatorado, então esse restante é um número primo.
        if(n > 1) fatores[cnt++] = n;
        int ans = m;
        // Agora é preciso usar o princÃ­pio da inclusão-exclusão nos fatores.
        // Podemos utilizar um bitmask para iterar sobre as possibilidades de incluir-excluir fatores.
        for(int mask = 1; mask < (1<<cnt); mask++){
            int x = 1;
            for(int i = 0; i < cnt; i++){
                if(mask&(1<<i)) x *= fatores[i];
            }
            x = m/x;
            if(__builtin_popcount(mask)%2 == 0) x = -x;
            ans -= x;
        }
        printf("%d\n", ans);
    }
    return 0;
}
