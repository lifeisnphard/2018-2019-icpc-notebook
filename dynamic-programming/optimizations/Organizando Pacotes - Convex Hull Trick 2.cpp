/*
Uma empresa de mineração extrai térbio, um metal raro usado para a construção de ímãs leves, a partir de areia de rio. Eles mineram um grande rio em N pontos de mineração, cada um deles identificado por sua distância a partir da origem do rio. Em cada ponto de mineração, uma pequena pilha ou amontoado de minério mineral altamente valorizado é extraido do rio.

Para recolher o minério mineral, a empresa reagrupa os N amontoados produzidos em um menor número de K pilhas ou montes maiores, cada um localizado num dos pontos de extração inicial. Os montes recém-formados são então recolhidos por caminhões.

Para reagrupar os N montes eles usam uma barca, o que na prática pode levar qualquer quantidade de minério mineral por ser bem larga. A barcaça começa na origem do rio e somente pode viajar rio abaixo, de modo que o amontoado de mineral produzido em um ponto X de mineração pode ser levado para um ponto Y de mineração somente se Y > X. Cada monte é movimentado completamente para outro ponto de mineração, ou não se move. O custo de mover um monte com peso W a partir de um ponto X de mineração para um ponto Y de mineração é W (Y - X). O custo total do agrupamento é a soma dos custos de cada movimento de um monte. Nota-se que um monte que não é movido não tem influência sobre o custo total.

Convex Hull Trick 2d:
Recurrence: dp[i][j] = min_(k < j){dp[i - 1][k] + b[k] * a[j]}
Condition: b[k] ≥ b[k + 1], a[j] ≤ a[j + 1]
Goes from O(k * n^2) to O(k * n)
*/
#include <bits/stdc++.h>
using namespace std;

#define len(x) ((int)(x).size())
#define endl '\n'

typedef long long lli;
typedef long long unsigned llu;
typedef long double llf;

// ---------------------------------------------------------------------

const int NK = 1e3 + 10;

int x[NK], w[NK];
lli sum_w[NK], sum_xw[NK], dp[NK][NK];

struct point{
	lli x, y;
	
	point operator - (point b){
		return {x - b.x, y - b.y};
	}
};

inline bool ccw(point a, point b){
	return (llf)a.x*b.y - (llf)a.y*b.x >= 0;
}

inline bool ccw(point a, point b, point c){
	return ccw(b - a, c - b);
}

inline lli calc(point p, int v){
	return p.x*v + p.y;
}

inline void Main(){
	int n, k;
	while(scanf("%d %d", &n, &k) != EOF){
		for(int i = 1; i <= n; i++){
			scanf("%d %d", &x[i], &w[i]);
		}
		for(int i = 1; i <= n; i++){
			sum_w[i] = sum_w[i - 1] + w[i];
			sum_xw[i] = sum_xw[i - 1] + x[i]*1LL*w[i];
		}
		for(int i = 1; i <= n; i++){
			dp[1][i] = x[i]*sum_w[i] - sum_xw[i];
		}
		for(int g = 2; g <= k; g++){
			int best = 0;
			vector<point> stk;
			for(int i = 1; i <= n; i++){
				if(i == 1){
					dp[g][i] = 0;
				}else{
					while(best + 1 < len(stk) && calc(stk[best], x[i]) >= calc(stk[best + 1], x[i])) best++;
					dp[g][i] = x[i]*sum_w[i] - sum_xw[i] + calc(stk[best], x[i]);
				}
				point nxt = {-sum_w[i], sum_xw[i] + dp[g - 1][i]};
				while(len(stk) > 1 && ccw(stk[len(stk) - 2], stk[len(stk) - 1], nxt)) stk.pop_back();
				stk.push_back(nxt);
			}
		}
		printf("%lld\n", dp[k][n]);
	}
}

// ---------------------------------------------------------------------

int main(){
	//ios_base::sync_with_stdio(0), cin.tie(0);
	//cout << fixed << setprecision(10);
	
	#ifndef ONLINE_JUDGE
		//freopen("in.txt", "r", stdin);
		//freopen("out.txt", "w", stdout);
	#endif
	
	Main();
	
	return 0;
}
