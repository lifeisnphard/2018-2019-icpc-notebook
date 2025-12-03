/*
Given a string, we need to find the total number of its distinct substrings.
*/
#include <bits/stdc++.h>
#define len(o) ((int)(o).size())
#define get(o, i) get<i>(o)
#define x first
#define y second
using namespace std;

const int N = 1e5 + 10;

char s[N];
int n, sa[N], suffixRank[N], k;

bool suff_cmp(int x, int y){
	if(suffixRank[x] != suffixRank[y]) return (suffixRank[x] < suffixRank[y]);
	x += (1 << k), y += (1 << k);
	if(x < n && y < n) return (suffixRank[x] < suffixRank[y]);
	return (x > y);
}

void build_sa(){
	for(int i = 0; i < n; i++){
		sa[i] = i, suffixRank[i] = s[i];
	}
	vector<int> tmp(n);
	for(k = 0; ; k++){
		sort(sa, sa + n, suff_cmp);
		for(int i = 1; i < n; i++){
			tmp[i] = tmp[i - 1] + suff_cmp(sa[i - 1], sa[i]);
		}
		for(int i = 0; i < n; i++){
			suffixRank[sa[i]] = tmp[i];
		}
		if(tmp[n - 1] == n - 1) break;
	}
}

int lcp[N];

void build_lcp(){
	vector<int> pos(n);
	for(int i = 0; i < n; i++) pos[sa[i]] = i;
	for(int i = 0, k = 0; i < n; i++){
		if(pos[i] == n - 1){
			k = 0;
			continue;
		}
		int j = sa[pos[i] + 1];
		while(i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
		lcp[pos[i]] = k;
		k = max(k - 1, 0);
	}
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%s", s);
		n = (int)strlen(s);
		build_sa();
		build_lcp();
		int ans = 0;
		for(int i = 0; i < n; i++){
			ans += n - sa[i];
			if(i > 0) ans -= lcp[i - 1];
		}
		printf("%d\n", ans);
	}
	return 0;
}
