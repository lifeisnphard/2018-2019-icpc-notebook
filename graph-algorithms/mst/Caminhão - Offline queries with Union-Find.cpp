/*
Ao planejar as rotas, a SBC se deparou com um problema: por razões de segurança, cada ponte da Nlogônia tem um limite máximo de peso permitido para os veículos que trafegam sobre ela. Devido ao grande número de pontes na Nlogônia, e ao elevado peso da mercadoria transportada, o diretor de operações da SBC pediu que você escrevesse um programa que determina o maior peso bruto que pode ser transportado entre os depósitos e os locais de prova.
*/
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
typedef pair<int,ii> iii;

const int N = 20100, M = 100100, S = 50100;

ii query[S];
iii edge[M];
vector<int> st[N];
int par[N], rnk[N], ans[S];

bool cmp(iii a, iii b){
    return (a.first>b.first);
}

int find(int x){
    if(par[x]==x) return x;
    return par[x] = find(par[x]);
}

void join(int a, int b, int v){
    a = find(a), b = find(b);
    if(a!=b){
		if(rnk[a] < rnk[b]) swap(a, b);
		else if(rnk[a] == rnk[b]) rnk[a]++;
		par[b] = a;
		
		// st[a] precisa conter a união dos dois vectors
		// preciso passar de b pra a
		
		bool to_swap = false;
		if(st[a].size() < st[b].size()){ // passo de a pra b
			to_swap = true;
			swap(a, b);
		}

        int tam = st[b].size();
        for(int i = 0; i < tam; i++){
            int id = st[b][i];
            if(ans[id]==-1){
                int x = query[id].first, y = query[id].second;
                if(find(x)==find(y)) ans[id] = v;
            }
            st[a].push_back(id);
        }
        st[b].clear();
		
		if(to_swap){ // troco os vectors
			st[a].swap(st[b]); // O(1)
		}
    }
}

int main(){
    int n, m, s;

    while(scanf("%d %d %d", &n, &m, &s)!=EOF){
        for(int i = 1; i <= n; i++){
            par[i] = i, rnk[i] = 0;
            st[i].clear();
        }
        for(int i = 0; i < m; i++){
            int a, b, p;
            scanf("%d %d %d", &a, &b, &p);
            edge[i] = iii(p,ii(a,b));
        }
        sort(edge,edge+m,cmp);
        for(int i = 0; i < s; i++){
            int a, b;
            scanf("%d %d", &a, &b);
            st[a].push_back(i), st[b].push_back(i);
            query[i] = ii(a,b);
            ans[i] = -1;
        }
        for(int i = 0; i < m; i++){
            int v = edge[i].first;
            int a = edge[i].second.first, b = edge[i].second.second;
            join(a,b,v);
        }
        for(int i = 0; i < s; i++){
            printf("%d\n", ans[i]);
        }
    }

    return 0;
}
