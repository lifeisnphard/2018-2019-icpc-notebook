/*
Given a string, count the number of distinct subsequences of it ( including empty subsequence ). For the uninformed, A subsequence of a string is a new string which is formed from the original string by deleting some of the characters without disturbing the relative positions of the remaining characters. 
*/
#include <stdio.h>
#include <string.h>
const int MAXS = 100100, MOD = 1000000007;

int last[26];
int dp[MAXS];

int mod(int num){
    return ((num%MOD)+MOD)%MOD;
}

int main(){
    int t;
    char str[MAXS];

    scanf("%d", &t);
    while(t--){
        scanf("%s", &str);
        for(int i = 0; i < 26; i++) last[i] = 0;

        dp[0] = 1;
        int tam = strlen(str);
        for(int i = 1; i <= tam; i++){
            dp[i] = 2*dp[i-1]%MOD;
            if(last[str[i-1]-'A']!=0) dp[i] = mod(dp[i]-dp[last[str[i-1]-'A']-1]);
            last[str[i-1]-'A'] = i;
        }
        printf("%d\n", dp[tam]);
    }

    return 0;
}
