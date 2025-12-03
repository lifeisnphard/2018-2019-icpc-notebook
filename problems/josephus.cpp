/*
Eles preferiram suicidar-se a serem capturados, e decidiram que iriam formar um círculo e começar a matar-se pulando de três em três. Josephus afirma que, por sorte ou talvez pela mão de Deus, ele permaneceu por último e preferiu entregar-se aos romanos a suicidar-se.

Haverá NC (1 ≤ NC ≤ 30 ) casos de teste. Em cada caso de teste de entrada haverá um par de números inteiros positivos n (1 ≤ n ≤ 10000 ) e k (1 ≤ k ≤ 1000). O  número n representa a quantidade de pessoas no círculo, numeradas de 1 até n. O número k representa o tamanho do salto de um homem até o próximo homem que será morto.

-
O(n) easy to code josephus algorithm
*/
#include <iostream>
#include <stdio.h>

#define MAXN 10000

using namespace std;

long int v[MAXN];

long int josephus(int n, int k){
    if(n == 1)
        return 1;
    else
        return (k-1 + josephus(n-1,k)) % n + 1;
}

int main(){
    int nc, n, k;
    scanf("%d", &nc);
    for(int i = 1; i <= nc; i++){
        scanf("%d %d", &n, &k);
        printf("Case %d: %d\n", i, josephus(n,k));
    }

    return 0;
}
