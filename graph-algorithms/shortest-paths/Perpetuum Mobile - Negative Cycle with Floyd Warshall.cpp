/*
Checking if there's a cycle such that the product of the edges is > 1
*/
#include <bits/stdc++.h>

using namespace std;

#define len(x) ((int)(x).size())
#define x first
#define y second

using ll = long long;
using llu = unsigned long long;
using ld = long double;

const ld EPS = 1e-9;
inline int cmp(ld x, ld y = 0, ld tol = EPS) {
  return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int N = 810;

ld g[N][N];

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			g[i][j] = 1e9;
		}
		g[i][i] = 0;
	}
	while(m--){
		int a, b; ld c;
		scanf("%d %d %Lf", &a, &b, &c);
		g[a][b] = min(g[a][b], -logl(c));
	}
	for(int k = 1; k <= n; k++){
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
			}
		}
	}
	for(int i = 1; i <= n; i++){
		if(cmp(g[i][i], 0) < 0){
			printf("inadmissible\n");
			return 0;
		}
	}
	printf("admissible\n");
	return 0;
}
