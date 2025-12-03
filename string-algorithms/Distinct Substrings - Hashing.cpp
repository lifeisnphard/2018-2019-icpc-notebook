/*
Given a string, we need to find the total number of its distinct substrings.
*/
#include <bits/stdc++.h>
using namespace std;

////////////// Prewritten code follows. Look down for solution. ////////////////
#define x first
#define y second
#define len(x) ((int)(x).size())
using pii = pair<int, int>;
using ll = long long;
using llu = long long unsigned;
using ld = long double;

const ld EPS = 1e-9;
inline int cmp(ld x, ld y = 0, ld tol = EPS) {
  return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int MOD = 1;
inline int mod (ll x, int m = MOD) {
  return (int)(((x%m) + m)%m);
}

////////////////////////// Solution starts below. //////////////////////////////

const int N = 1010;

const int P1 = 257, P2 = 263, P3 = 268;
const int MOD1 = 1e9 + 7, MOD2 = 1e9 + 9, MOD3 = 1e9 + 21;

struct Hash{
	int m;
	int pot[N], h[N];
	
	Hash(char s[], int p, int _m): m(_m){
		int n = strlen(s);
		pot[0] = 1, h[0] = s[0];
		for(int i = 1; i < n; i++){
			pot[i] = mod(pot[i - 1]*1LL*p, m);
			h[i] = mod(h[i - 1]*1LL*p + s[i], m);
		}
	}
	
	int get(int l, int r){
		int ret = h[r];
		if(l > 0) ret = mod(ret - h[l - 1]*1LL*pot[r - l + 1], m);
		return ret;
	}
};

char s[N];

int solve(int n){
	vector<pair<pair<int, int>, int>> v;
	
	Hash hash1(s, P1, MOD1), hash2(s, P2, MOD2), hash3(s, P3, MOD3);
	for(int i = 0; i < n; i++){
		for(int j = i; j < n; j++){
			v.push_back({{hash1.get(i, j), hash2.get(i, j)}, hash3.get(i, j)});
		}
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	return len(v);
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%s", s);
		printf("%d\n", solve((int)strlen(s)));
	}
	return 0;
}
