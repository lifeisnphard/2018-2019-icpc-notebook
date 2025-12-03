/*
You are given an array a consisting of n integers. You have to process q queries to this array; each query is given as four numbers l, r, x and y, denoting that for every i such that l ≤ i ≤ r and ai = x you have to set ai equal to y.

Print the array after all queries are processed.
*/
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
#define x first
#define y second
using namespace std;

const int N = 2e5 + 10, C = 110;

int a[N];
int seg[4*N][C];

void build(int idx, int l, int r){
	if(l != r){
		int mid = (l + r)/2;
		build(2*idx + 1, l, mid);
		build(2*idx + 2, mid + 1, r);
	}
	for(int i = 1; i <= 100; i++){
		seg[idx][i] = i;
	}
}

inline void push(int idx, int l, int r){
	for(int i = 1; i <= 100; i++){
		seg[2*idx + 1][i] = seg[idx][seg[2*idx + 1][i]];
		seg[2*idx + 2][i] = seg[idx][seg[2*idx + 2][i]];
	}
	for(int i = 1; i <= 100; i++){
		seg[idx][i] = i;
	}
}

void modify(int idx, int l, int r, int a, int b, int x, int y){
	if(l > b || r < a) return;
	if(l >= a && r <= b){
		for(int i = 1; i <= 100; i++){
			if(seg[idx][i] == x) seg[idx][i] = y;
		}
		return;
	}
	push(idx, l, r);
	int mid = (l + r)/2;
	modify(2*idx + 1, l, mid, a, b, x, y);
	modify(2*idx + 2, mid + 1, r, a, b, x, y);
}

int query(int idx, int l, int r, int pos, int x){
	if(l == r) return seg[idx][x];
	int mid = (l + r)/2;
	push(idx, l, r);
	if(pos <= mid){
		return query(2*idx + 1, l, mid, pos, x);
	}
	return query(2*idx + 2, mid + 1, r, pos, x);
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	build(0, 1, n);
	int q;
	scanf("%d", &q);
	while(q--){
		int l, r, x, y;
		scanf("%d %d %d %d", &l, &r, &x, &y);
		modify(0, 1, n, l, r, x, y);
	}
	for(int i = 1; i <= n; i++){
		printf("%d ", query(0, 1, n, i, a[i]));
	}
	printf("\n");
	return 0;
}
