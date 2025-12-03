/*
Roman planted a tree consisting of n vertices. Each vertex contains a lowercase English letter. Vertex 1 is the root of the tree, each of the n - 1 remaining vertices has a parent in the tree. Vertex is connected with its parent by an edge. The parent of vertex i is vertex pi, the parent index is always less than the index of the vertex (i.e., pi < i).

Roma gives you m queries, the i-th of which consists of two numbers vi, hi. Let's consider the vertices in the subtree vi located at depth hi. Determine whether you can use the letters written at these vertices to make a string that is a palindrome. The letters that are written in the vertexes, can be rearranged in any order to make a palindrome, but all letters should be used.
*/
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define fx first
#define fy second

typedef long long ll;

const int NM = 500100;

char s[NM];
vector<int> adj[NM];
vector<pair<int, int> > qry[NM];
int level[NM], subsize[NM], sc[NM], qtd[NM][26];
bool ans[NM];

void dfs(int u, int l){
    level[u] = l;
    subsize[u] = 1, sc[u] = -1;
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        dfs(v, l + 1);
        subsize[u] += subsize[v];
        if(sc[u] == -1 || subsize[v] > subsize[sc[u]]) sc[u] = v;
    }
}

void dfs_update(int u, int val){
    qtd[level[u]][s[u] - 'a'] += val;
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        dfs_update(v, val);
    }
}

void solve(int u){
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(v != sc[u]){
            solve(v);
            dfs_update(v, 1);
        }
    }
    if(sc[u] != -1){
        solve(sc[u]);
        for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(v != sc[u]){
                dfs_update(v, -1);
            }
        }
    }
    qtd[level[u]][s[u] - 'a']++;
    for(int i = 0; i < qry[u].size(); i++){
        int h = qry[u][i].fx, q = qry[u][i].fy;
        int odd = 0;
        for(int j = 0; j < 26; j++){
            if(qtd[h][j]%2 == 1) odd++;
        }
        ans[q] = (odd <= 1);
    }
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
    #endif

    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 2; i <= n; i++){
        int p;
        scanf("%d", &p);
        adj[p].push_back(i);
    }
    dfs(1, 1);
    scanf("%s", s + 1);
    for(int i = 0; i < m; i++){
        int v, h;
        scanf("%d %d", &v, &h);
        qry[v].push_back(mp(h, i));
    }
    solve(1);
    for(int i = 0; i < m; i++){
        printf("%s\n", ans[i]? "Yes" : "No");
    }

    return 0;
}
