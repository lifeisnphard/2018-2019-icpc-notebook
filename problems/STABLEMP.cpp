/*
There are given n men and n women. Each woman ranks all men in order of her preference (her first choice, her second choice, and so on). Similarly, each man sorts all women according to his preference. The goal is to arrange n marriages in such a way that if a man m prefers some woman w more than his wife, then w likes her husband more than m. In this way, no one leaves his partner to marry somebody else. This problem always has a solution and your task is to find one.
*/
#include <bits/stdc++.h>
using namespace std;
 
const int N = 510;
 
int n;
deque<int> man_pref[N], wom_pref[N];
int likes[N][N], match[N];
 
int main(){
    int t;
    scanf("%d", &t);
    for(int k = 0; k < t; k++){
        scanf("%d", &n);
        deque<int> freeWoman;
        for(int i = 1; i <= n; i++){
            freeWoman.push_back(i);
            man_pref[i].clear();
            wom_pref[i].clear();
            match[i] = 0;
        }
        for(int i = 1, w; i <= n; i++){
            scanf("%d", &w);
            for(int j = 1, m; j <= n; j++){
                scanf("%d", &m);
                wom_pref[w].push_back(m);
            }
        }
        for(int i = 1, m; i <= n; i++){
            scanf("%d", &m);
            for(int j = 1, w; j <= n; j++){
                scanf("%d", &w);
                man_pref[m].push_back(w);
                likes[m][w] = n - j + 1;
            }
        }
        while(!freeWoman.empty()){
            int w = freeWoman.front();
            int m = wom_pref[w].front();
            wom_pref[w].pop_front();
            if(!match[m]){
                match[m] = w;
                freeWoman.pop_front();
            }else if(likes[m][w] > likes[m][match[m]]){
                freeWoman.pop_front();
                freeWoman.push_back(match[m]);
                match[m] = w;
            }
        }
        for(int m = 1; m <= n; m++){
            printf("%d %d\n", m, match[m]);
        }
    }
    return 0;
}
