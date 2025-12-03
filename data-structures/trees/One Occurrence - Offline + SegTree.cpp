/*
You are given an array a consisting of n integers, and q queries to it. i-th query is denoted by two integers l_i and r_i. For each query, you have to find any integer that occurs exactly once in the subarray of a from index l_i to index r_i.
*/
#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int NQA = 5e5 + 10;

int a[NQA];
vector<pair<int, int>> qrs[NQA];
int last[NQA], ans[NQA];
pair<int, int> seg[4*NQA];

void modify(int idx, int l, int r, int pos, int val){
	if(l == r){
		seg[idx] = {val, pos};
	}else{
		int mid = (l + r)/2;
		if(pos <= mid) modify(2*idx + 1, l, mid, pos, val);
		else modify(2*idx + 2, mid + 1, r, pos, val);
		seg[idx] = min(seg[2*idx + 1], seg[2*idx + 2]);
	}
}

pair<int, int> query(int idx, int l, int r, int a, int b){
	if(l > b || r < a) return {1e9, 1e9};
	if(l >= a && r <= b) return seg[idx];
	
	int mid = (l + r)/2;
	return min(query(2*idx + 1, l, mid, a, b), query(2*idx + 2, mid + 1, r, a, b));
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	int q;
	scanf("%d", &q);
	for(int i = 0; i < q; i++){
		int l, r;
		scanf("%d %d", &l, &r);
		qrs[r].push_back({l, i});
	}
	for(int i = 1; i <= n; i++){
		if(last[a[i]]) modify(0, 1, n, last[a[i]], last[a[i]]);
		modify(0, 1, n, i, last[a[i]]);
		last[a[i]] = i;
		for(auto qry : qrs[i]){
			int l = qry.x, r = i, idx = qry.y;
			auto go = query(0, 1, n, l, r);
			if(go.x < l) ans[idx] = a[go.y];
		}
	}
	for(int i = 0; i < q; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
