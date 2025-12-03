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

const int NQA = 5e5 + 10, BSIZE = 710;

int n;
int a[NQA];
vector<pair<pair<int, int>, int>> qrs;
int freq[NQA], qtd_ones[BSIZE];
int ans[NQA];

inline void mo_add(int val){
	freq[val]++;
	if(freq[val] == 1) qtd_ones[val/BSIZE]++;
	else if(freq[val] == 2) qtd_ones[val/BSIZE]--;
}

inline void mo_rmv(int val){
	freq[val]--;
	if(freq[val] == 0) qtd_ones[val/BSIZE]--;
	else if(freq[val] == 1) qtd_ones[val/BSIZE]++;
}

inline int mo_get(){
	int block = -1;
	for(int i = 0; i < BSIZE; i++){
		if(qtd_ones[i]){
			block = i;
			break;
		}
	}
	if(block == -1) return 0;
	
	int offset = block*BSIZE;
	for(int i = 0; i < BSIZE; i++){
		if(freq[offset + i] == 1) return offset + i;
	}
	assert(false);
	return 0;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	int q;
	scanf("%d", &q);
	for(int i = 0; i < q; i++){
		int l, r;
		scanf("%d %d", &l, &r); l--, r--;
		qrs.push_back({{l, r}, i});
	}
	sort(qrs.begin(), qrs.end(), [](auto a, auto b){
		int block = a.x.x/BSIZE;
		if(block != b.x.x/BSIZE)
			return (block < b.x.x/BSIZE);
		if(block & 1)
			return (a.x.y > b.x.y);
		return (a.x.y < b.x.y);
	});
	int curL = 0, curR = -1;
	for(auto qry : qrs){
		int l = qry.x.x, r = qry.x.y, idx = qry.y;
		
		while(curL < l) mo_rmv(a[curL++]);
		while(curL > l) mo_add(a[--curL]);
		while(curR < r) mo_add(a[++curR]);
		while(curR > r) mo_rmv(a[curR--]);
		
		ans[idx] = mo_get();
	}
	for(int i = 0; i < q; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
