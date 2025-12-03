/*
T test cases. Given an integer n (1 <= n <= 10^6). Compute the value of the totient.
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;

int phi[N];

void pre(){
    for(int i = 1; i < N; i++){
        phi[i] = i;
    }
    for(int i = 1; i < N; i++){
        for(int j = i + i; j < N; j += i){
            phi[j] -= phi[i];
        }
    }
}

int main(){
    pre();

    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        printf("%d\n", phi[n]);
    }
    return 0;
}
