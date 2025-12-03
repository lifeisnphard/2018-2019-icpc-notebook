/*
Given a sequence of n numbers a1, a2, ..., an and a number of d-queries. A d-query is a pair (i, j) (1 ≤ i ≤ j ≤ n). For each d-query (i, j), you have to return the number of distinct elements in the subsequence ai, ai+1, ..., aj.
*/
#include <bits/stdc++.h>
using namespace std;
 
const int N = 3e4 + 10, A = 1e6 + 10;
const int LOGN = 17, MAXNODES = 4*N + 2*N*LOGN;
 
int root[N];
int node_cnt, sum[MAXNODES], lc[MAXNODES], rc[MAXNODES];
 
int build(int l, int r){
    int id = ++node_cnt;
    if(l != r){
        int mid = (l + r)/2;
        lc[id] = build(l, mid);
        rc[id] = build(mid + 1, r);
        sum[id] = sum[lc[id]] + sum[rc[id]];
    }
    return id;
}
 
int modify(int id, int l, int r, int p, bool val){
    int nid = ++node_cnt;
    if(l == r){
        sum[nid] = val;
    }else{
        int mid = (l + r)/2;
        if(p <= mid){
            lc[nid] = modify(lc[id], l, mid, p, val);
            rc[nid] = rc[id];
        }else{
            lc[nid] = lc[id];
            rc[nid] = modify(rc[id], mid + 1, r, p, val);
        }
        sum[nid] = sum[lc[nid]] + sum[rc[nid]];
    }
    return nid;
}
 
int query(int id, int l, int r, int a, int b){
    if(l > b || r < a) return 0;
    if(l >= a && r <= b) return sum[id];
    int mid = (l + r)/2;
    return query(lc[id], l, mid, a, b) + query(rc[id], mid + 1, r, a, b);
}
 
int last[A];
 
int main(){
    int n;
    scanf("%d", &n);
    root[0] = build(1, n);
    for(int i = 1, a; i <= n; i++){
        scanf("%d", &a);
        int id = root[i - 1];
        if(last[a] != 0){
            id = modify(id, 1, n, last[a], 0);
        }
        root[i] = modify(id, 1, n, i, 1);
        last[a] = i;
    }
    int q;
    scanf("%d", &q);
    for(int i = 1, a, b; i <= q; i++){
        scanf("%d %d", &a, &b);
        printf("%d\n", query(root[b], 1, n, a, b));
    }
    return 0;
}
