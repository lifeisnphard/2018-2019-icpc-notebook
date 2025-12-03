/*
Given a string, we need to find the total number of its distinct substrings.
*/
#include <bits/stdc++.h>
#define len(o) ((int)(o).size())
#define get(o, i) get<i>(o)
#define x first
#define y second
using namespace std;

const int N = 1010;

char s[N];

int solve(int n){
	int ret = 0;
	vector<int> dp(n);
	for(int i = 1; i <= n; i++){
		int mx = 0;
		for(int j = i - 1; j >= 1; j--){
			if(s[i - 1] != s[j - 1]) dp[j] = 0;
			else mx = max(mx, dp[j] = dp[j - 1] + 1);
		}
		ret += i - mx;
	}
	return ret;
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
