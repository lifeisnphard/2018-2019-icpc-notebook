/*
The city of Y-O is a network of two-way streets and junctions with the following properties:

There is no more than one street between each pair of junctions.
Every junction is connected to every other junction either directly via a street or through other junctions by a unique path.
When a light is placed at a junction, all the streets meeting at this junction are also lit.
A valid lighting is a set of junctions such that if lights were placed at these, all the streets would be lit. An optimal lighting is a valid lighting such that it contains the least number of junctions.

The task is divided into two subtasks:

Find the number of lights in an optimal lighting.
Find the total number of such optimal lightings in the city.

N <= 100010
*/
#include <bits/stdc++.h>
using namespace std;
 
const int N = 100010 + 10, MOD = 10007;
 
vector<int> adj[N];
int a[N][2], b[N][2];
 
void dfs(int u, int p = -1){
    a[u][0] = 0, a[u][1] = 1;
    b[u][0] = 1, b[u][1] = 1;
 
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(v != p){
            dfs(v, u);
 
            a[u][0] += a[v][1];
            a[u][1] += min(a[v][0], a[v][1]);
 
            b[u][0] = (b[u][0]*b[v][1])%MOD;
 
            if(a[v][0] < a[v][1]){
                b[u][1] = (b[u][1]*b[v][0])%MOD;
            }else if(a[v][0] > a[v][1]){
                b[u][1] = (b[u][1]*b[v][1])%MOD;
            }else{
                b[u][1] = (b[u][1]*(b[v][0] + b[v][1]))%MOD;
            }
        }
    }
}
 
int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++){
            adj[i].clear();
        }
        for(int i = 1; i < n; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(1);
        printf("%d ", min(a[1][0], a[1][1]));
        if(a[1][0] < a[1][1]){
            printf("%d\n", b[1][0]);
        }else if(a[1][0] > a[1][1]){
            printf("%d\n", b[1][1]);
        }else{
            printf("%d\n", (b[1][0] + b[1][1])%MOD);
        }
    }
    return 0;
} 
