/*
It's Christmas time! PolandBall and his friends will be giving themselves gifts. There are n Balls overall. Each Ball has someone for whom he should bring a present according to some permutation p, pi ≠ i for all i.

Unfortunately, Balls are quite clumsy. We know earlier that exactly k of them will forget to bring their gift. A Ball number i will get his present if the following two constraints will hold:

1. Ball number i will bring the present he should give.
2. Ball x such that px = i will bring his present.

What is minimum and maximum possible number of kids who will not get their present if exactly k Balls will forget theirs?
*/
#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int NK = 1e6 + 10;

int p[NK], qtd[NK];
bool seen[NK];
int dp[NK];

int get_minimum(int n, int k){
	int lim = min(k, n - k);
	
	dp[0] = 0;
	for(int i = 1; i <= lim; i++){
		dp[i] = -1;
	}
	for(int i = 1; i <= n; i++) if(qtd[i]){ // O(sqrt(n))
		int val = i, many = qtd[i];
		for(int j = 0; j <= lim; j++){
			if(dp[j] != -1){
				dp[j] = 0;
			}else if(j >= val && dp[j - val] != -1 && dp[j - val] < many){
				dp[j] = dp[j - val] + 1;
			}else{
				dp[j] = -1;
			}
		}
	}
	return dp[lim] != -1 ? k : k + 1;
}

int get_maximum(int n, int k){
	int cnt = 0;
	for(int i = 1; i <= n; i++){
		cnt += i/2 * qtd[i];
	}
	return min(min(cnt, k)*2 + k - min(cnt, k), n);
}

int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++){
		scanf("%d", &p[i]);
	}
	for(int i = 1; i <= n; i++) if(!seen[i]){
		int u = i, cnt = 0;
		while(!seen[u]){
			seen[u] = true;
			u = p[u];
			cnt++;
		}
		qtd[cnt]++;
	}
	printf("%d %d\n", get_minimum(n, k), get_maximum(n, k));
	return 0;
}
