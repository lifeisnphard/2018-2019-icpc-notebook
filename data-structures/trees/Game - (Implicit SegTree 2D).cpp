/*
Bazza and Shazza are playing a game. The board is a grid of cells, with R rows numbered 0, …, R - 1, and C columns, numbered 0, …, C - 1. We let (P, Q) denote the cell in row P and column Q. Each cell contains a non-negative integer, and at the beginning of the game all of these integers are zero.

The game proceeds as follows. At any time, Bazza may either:

update a cell (P, Q), by assigning the integer that it contains
ask Shazza to calculate the greatest common divisor (GCD) of all integers within a rectangular block of cells, with opposite corners (P, Q) and (U, V) inclusive.
Bazza will take NU + NQ actions (updating cells NU times and asking questions NQ times) before he gets bored and goes outside to play cricket.

Your task is to work out the correct answers.
R <= 10^9, C <= 10^9, Nu <= 22,000, Nq <= 250,000
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long lli;

lli gcd(lli a, lli b){
	if(b == 0) return a;
	return gcd(b, a%b);
}

int n, m;

struct Nodey{
	lli val;
	Nodey *L, *R;
	
	Nodey(): val(0), L(NULL), R(NULL){}
};

struct Nodex{
	Nodey *inner;
	Nodex *L, *R;
	
	Nodex(): inner(NULL), L(NULL), R(NULL){}
} *root = NULL;

void updatey(Nodey *&node, int l, int r, int y, lli val){
	if(!node) node = new Nodey();
	if(l == r){
		node->val = val;
	}else{
		int mid = (l + r)/2;
		if(y <= mid){
			updatey(node->L, l, mid, y, val);
		}else{
			updatey(node->R, mid + 1, r, y, val);
		}
		node->val = gcd(node->L? node->L->val : 0, node->R? node->R->val : 0);
	}
}

void update2y(Nodey *&node, int l, int r, int y, lli val, Nodey *a, Nodey *b){
	if(!node) node = new Nodey();
	if(l == r){
		node->val = gcd(a? a->val : 0, b? b->val : 0);
	}else{
		int mid = (l + r)/2;
		if(y <= mid){
			update2y(node->L, l, mid, y, val, a? a->L : NULL, b? b->L : NULL);
		}else{
			update2y(node->R, mid + 1, r, y, val, a? a->R : NULL, b? b->R : NULL);
		}
		node->val = gcd(node->L? node->L->val : 0, node->R? node->R->val : 0);
		//node->val = gcd(a? a->val : 0, b? b->val : 0);
	}
}

void updatex(Nodex *&node, int l, int r, int x, int y, lli val){
	if(!node) node = new Nodex();
	if(l == r){
		updatey(node->inner, 0, m - 1, y, val);
	}else{
		int mid = (l + r)/2;
		if(x <= mid){
			updatex(node->L, l, mid, x, y, val);
		}else{
			updatex(node->R, mid + 1, r, x, y, val);
		}
		// HARD
		update2y(node->inner, 0, m - 1, y, val, node->L? node->L->inner : NULL, node->R? node->R->inner : NULL);
	}
}

lli queryy(Nodey *node, int l, int r, int a, int b){
	if(!node || l > b || r < a) return 0;
	if(l >= a && r <= b) return node->val;
	int mid = (l + r)/2;
	return gcd(queryy(node->L, l, mid, a, b), queryy(node->R, mid + 1, r, a, b));
}

lli queryx(Nodex *node, int l, int r, int a, int b, int ay, int by){
	if(!node || l > b || r < a) return 0;
	if(l >= a && r <= b) return queryy(node->inner, 0, m - 1, ay, by);
	int mid = (l + r)/2;
	return gcd(queryx(node->L, l, mid, a, b, ay, by), queryx(node->R, mid + 1, r, a, b, ay, by));
}

int main(){
	int q;
	scanf("%d %d %d", &n, &m, &q);
	while(q--){
		int t;
		scanf("%d", &t);
		if(t == 1){
			int x, y; lli val;
			scanf("%d %d %lld", &x, &y, &val);
			updatex(root, 0, n - 1, x, y, val);
		}else{
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			printf("%lld\n", queryx(root, 0, n - 1, x1, x2, y1, y2));
		}
	}
	return 0;
}
