/*
Problem:
Kalila and Dimna are two jackals living in a huge jungle. One day they decided to join a logging factory in order to make money.

The manager of logging factory wants them to go to the jungle and cut n trees with heights a1, a2, ..., an. They bought a chain saw from a shop. Each time they use the chain saw on the tree number i, they can decrease the height of this tree by one unit. Each time that Kalila and Dimna use the chain saw, they need to recharge it. Cost of charging depends on the id of the trees which have been cut completely (a tree is cut completely if its height equal to 0). If the maximum id of a tree which has been cut completely is i (the tree that have height ai in the beginning), then the cost of charging the chain saw would be bi. If no tree is cut completely, Kalila and Dimna cannot charge the chain saw. The chainsaw is charged in the beginning. We know that for each i < j, ai < aj and bi > bj and also bn = 0 and a1 = 1. Kalila and Dimna want to cut all the trees completely, with minimum cost.

They want you to help them! Will you?

Convex Hull Trick 1d:
Recurrence: dp_i = min_(j < i){dp[j] + b[j]*a[i]}
Condition: b[j] ≥ b[j + 1], a[i] ≤ a[i + 1]
Goes from O(n^2) to O(n)
*/
#include <bits/stdc++.h>
using namespace std;

#define len(x) ((int)(x).size())
#define endl '\n'

typedef long long lli;
typedef long long unsigned llu;
typedef long double llf;

// ---------------------------------------------------------------------

const int N = 1e5 + 10;

int a[N], b[N];
lli dp[N];

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
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	
	int best = 0;
	vector<point> stk;
	for(int i = 1; i <= n; i++){
		if(i == 1){
			dp[i] = 0;
		}else{
			while(best + 1 < len(stk) && calc(stk[best], a[i]) >= calc(stk[best + 1], a[i])) best++;
			dp[i] = calc(stk[best], a[i]);
		}
		point nxt = {b[i], dp[i]};
		while(len(stk) > 1 && ccw(stk[len(stk) - 2], stk[len(stk) - 1], nxt)) stk.pop_back();
		stk.push_back(nxt);
	}
	printf("%lld\n", dp[n]);
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
