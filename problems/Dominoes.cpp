/*
You have a set of dominoes. Each domino is a rectangular tile with a line dividing its face into two square ends. Can you put all dominoes in a line one by one from left to right so that any two dominoes touched with the sides that had the same number of points? You can rotate the dominoes, changing the left and the right side (domino "1-4" turns into "4-1").

Input
The first line contains number n (1  ≤  n  ≤  100). Next n lines contains the dominoes. Each of these lines contains two numbers — the number of points (spots) on the left and the right half, correspondingly. The numbers of points (spots) are non-negative integers from 0 to 6.

Output
Print "No solution", if it is impossible to arrange the dominoes in the required manner. If the solution exists, then describe any way to arrange the dominoes. You put the dominoes from left to right. In each of n lines print the index of the domino to put in the corresponding position and then, after a space, character "+" (if you don't need to turn the domino) or "–" (if you need to turn it).
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 110;

int a[N], b[N];
int adj[7][7], degree[7];
deque<int> ans;
bool used[N];

void dfs(int u){
    for(int v = 0; v < 7; v++){
        if(adj[u][v]){
            adj[u][v]--, adj[v][u]--;
            dfs(v);
        }
    }
    ans.push_front(u);
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d %d", &a[i], &b[i]);
        adj[a[i]][b[i]]++, adj[b[i]][a[i]]++;
        degree[a[i]]++, degree[b[i]]++;
    }
    int start = a[1], qtd_odd = 0;
    for(int i = 0; i < 7; i++){
        if(degree[i]%2 == 1){
            start = i;
            qtd_odd++;
        }
    }
    if(qtd_odd > 2){
        printf("No solution\n");
        return 0;
    }
    dfs(start);
    if(ans.size() != n + 1){
        printf("No solution\n");
        return 0;
    }
    for(int i = 0; i < n; i++){
        for(int j = 1; j <= n; j++) if(!used[j]){
            if(ans[i] == a[j] && ans[i + 1] == b[j]){
                printf("%d +\n", j);
                used[j] = true;
                break;
            }else if(ans[i] == b[j] && ans[i + 1] == a[j]){
                printf("%d -\n", j);
                used[j] = true;
                break;
            }
        }
    }
    return 0;
}
