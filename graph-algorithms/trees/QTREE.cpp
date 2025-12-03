/*
You are given a tree with N nodes, and edges numbered 1, 2, 3...N-1.

We will ask you to perfrom some instructions of the following form:

CHANGE i ti : change the cost of the i-th edge to ti
or
QUERY a b : ask for the maximum edge cost on the path from node a to node b
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;

// TREE --------------------------------------------------------
int a[N], b[N];
vector<pair<int, int> > adj[N];
int n, logN, parent[N], level[N], subsize[N], sc[N], se[N];

void graph_clear(){
    for(int i = 1; i <= n; i++){
        adj[i].clear();
    }
}

void dfs(int u, int p, int l = 0){
    level[u] = l;
    parent[u] = p;
    subsize[u] = 1, sc[u] = -1;
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i].first, cost = adj[u][i].second;
        if(v != p){
            dfs(v, u, l + 1);
            subsize[u] += subsize[v];
            if(sc[u] == -1 || subsize[v] > subsize[sc[u]]){
                sc[u] = v, se[u] = cost;
            }
        }
    }
}

// Segment Tree ------------------------------------------------------
int seg[4*N];

void seg_clear(){
    for(int i = 0; i < 4*N; i++){
        seg[i] = 0;
    }
}

void seg_modify(int idx, int l, int r, int p, int val){
    if(l > p || r < p) return;
    if(l == r){
        seg[idx] = val;
        return;
    }
    int mid = (l + r)/2;
    seg_modify(2*idx + 1, l, mid, p, val);
    seg_modify(2*idx + 2, mid + 1, r, p, val);
    seg[idx] = max(seg[2*idx + 1], seg[2*idx + 2]);
}

int seg_query(int idx, int l, int r, int a, int b){
    if(l > b || r < a) return 0;
    if(l >= a && r <= b) return seg[idx];
    int mid = (l + r)/2;
    return max(seg_query(2*idx + 1, l, mid, a, b), seg_query(2*idx + 2, mid + 1, r, a, b));
}
// HLD ---------------------------------------------------------------
int chain_cnt, chain[N], chainHead[N];
int pos_cnt, posInSeg[N];

void hld_clear(){
    chain_cnt = 0, pos_cnt = 0;
}

void hld(int u, int cost = 0, int chainIdx = ++chain_cnt, bool head = true){
    if(head) chainHead[chainIdx] = u;
    chain[u] = chainIdx;
    posInSeg[u] = ++pos_cnt;
    seg_modify(0, 1, n, posInSeg[u], cost);
    if(sc[u] != -1){
        hld(sc[u], se[u], chainIdx, false);
        for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i].first, cost = adj[u][i].second;
            if(v != parent[u] && v != sc[u]){
                hld(v, cost);
            }
        }
    }
}

int hld_query(int a, int b){
	if(chain[a] == chain[b]){
		if(level[a] > level[b]) swap(a, b);
		return seg_query(0, 1, n, posInSeg[a] + 1, posInSeg[b]);
	}
	if(level[chainHead[chain[a]]] < level[chainHead[chain[b]]]) swap(a, b);
	int head = chainHead[chain[a]];
	return max(seg_query(0, 1, n, posInSeg[head], posInSeg[a]), hld_query(parent[head], b));
}

// Main --------------------------------------------------------------
int main(){
    int t;
    scanf("%d", &t);
    for(int k = 0; k < t; k++){
        scanf("%d", &n);
        logN = log2(n);
        for(int i = 1, c; i < n; i++){
            scanf("%d %d %d", &a[i], &b[i], &c);
            adj[a[i]].push_back(make_pair(b[i], c));
            adj[b[i]].push_back(make_pair(a[i], c));
        }
        dfs(1, 1);
        hld(1);
        char s[10];
        while(scanf("%s", s) && strcmp(s, "DONE")){
            if(!strcmp(s, "CHANGE")){
                int i, c;
                scanf("%d %d", &i, &c);
                if(a[i] == parent[b[i]]){
                    seg_modify(0, 1, n, posInSeg[b[i]], c);
                }else{
                    seg_modify(0, 1, n, posInSeg[a[i]], c);
                }
            }else{
                int a, b;
                scanf("%d %d", &a, &b);
                printf("%d\n", hld_query(a, b));
            }
        }
        graph_clear(), seg_clear(), hld_clear();
    }
    return 0;
}
