/*
T test cases. Given an integer n (1 <= n <= 10^6). Compute the value of the totient.
*/
#include <bits/stdc++.h>
using namespace std;

int power(int a, int x){
    int ret = 1;
    for(int j = 0; j < x; j++){
        ret *= a;
    }
    return ret;

}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n, ans = 1;
        scanf("%d", &n);
        for(int i = 2; i*i <= n; i++){
            int cnt = 0;
            while(n%i == 0){
                n /= i;
                cnt++;
            }
            if(cnt > 0){
                int pot = power(i, cnt);
                ans *= pot - pot/i;
            }
        }
        if(n > 1){
            ans *= n - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
