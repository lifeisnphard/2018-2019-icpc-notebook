/*
Floyd Warshall estendido
*/
#include <stdio.h>

const int MAXN = 110, INF = 0x3f3f3f3f;

int dist[MAXN][MAXN][MAXN];

int min(int a, int b){return (a<b)?a:b;}

int main(){
    int k = 0, n, m, u, v, w, c, t;

    while(scanf("%d %d", &n, &m)!=EOF){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                for(int k = 0; k <= n; k++) dist[i][j][k] = INF;
            }
            dist[i][i][0] = 0;
        }
        while(m--){
            scanf("%d %d %d", &u, &v, &w);
            dist[u][v][0] = min(dist[u][v][0],w);
        }
        for(int k = 1; k <= n; k++){
            for(int i = 1; i <= n; i++){
                for(int j = 1; j <= n; j++){
                    dist[i][j][k] = min(dist[i][j][k-1], dist[i][k][k-1] + dist[k][j][k-1]);
                }
            }
        }
        scanf("%d", &c);
        printf("Instancia %d\n", ++k);
        while(c--){
            scanf("%d %d %d", &u, &v, &t);
            printf("%d\n", (dist[u][v][t]<INF)?dist[u][v][t]:-1);
        }
        printf("\n");
    }

    return 0;
}
