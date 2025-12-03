/*
2-SAT implementation
*/
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
typedef pair<int,int> ii;

const int MAXP = 10100;
const int WHITE = 0, GREY = 1, BLACK = 2;

vector<ii> adj[2][MAXP], pilha;
int index, num[2][MAXP], low[2][MAXP], color[2][MAXP], comp[2][MAXP], qtdecomp;

void dfs(int b, int u){
    num[b][u] = low[b][u] = ++index;
    pilha.push_back(ii(b,u));
    color[b][u] = GREY;

    int tam = adj[b][u].size();
    for(int i = 0; i < tam; i++){
        int bv = adj[b][u][i].first, v = adj[b][u][i].second;
        if(color[bv][v]==WHITE){
            dfs(bv,v);
            low[b][u] = min(low[b][u],low[bv][v]);
        }else if(color[bv][v]==GREY){
            low[b][u] = min(low[b][u],low[bv][v]);
        }
    }

    if(num[b][u]==low[b][u]){
        // Novo componente fortemente conexo
        qtdecomp++;
        int bv, v;
        do{
            ii aux = pilha.back();
            pilha.pop_back();
            bv = aux.first, v = aux.second;
            comp[bv][v] = qtdecomp;
            color[bv][v] = BLACK;
        }while(bv!=b || v!=u);
    }
}

int main(){
    int c, p, x, y, s, t;

    while(scanf("%d %d", &c, &p)){
        if(c==0 && p==0) break;
        index = qtdecomp = 0;
        pilha.clear();
        for(int i = 1; i <= p; i++){
            comp[0][i] = comp[1][i] = 0;
            color[0][i] = color[1][i] = WHITE;
            adj[0][i].clear(), adj[1][i].clear();
        }
        for(int i = 0; i < c; i++){
            scanf("%d %d %d %d", &x, &y, &s, &t);
            if(min(x,y)==0) x = y = max(x,y);
            if(min(s,t)==0) s = t = max(s,t);
            if(x!=0){
                adj[0][x].push_back(ii(1,y));
                adj[0][y].push_back(ii(1,x));
            }
            if(s!=0){
                adj[1][s].push_back(ii(0,t));
                adj[1][t].push_back(ii(0,s));
            }
        }
        for(int i = 1; i <= p; i++){
            for(int b = 0; b < 2; b++) if(color[b][i]==WHITE) dfs(b,i);
        }
        bool resp = true;
        for(int i = 1; i <= p; i++){
            if(comp[0][i]==comp[1][i]){
                resp = false;
                break;
            }
        }
        printf("%s\n", resp?"yes":"no");
    }

    return 0;
}
