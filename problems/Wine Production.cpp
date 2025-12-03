/*
In order for a grape to reach optimum development, it is important to known how many different temperatures it faced during its growth and in how many days each of these temperatures were repeated. Recent studies show that the quality of the wine is deeply correlated with the following number. Consider the growth period for the grape and count, in those days, how many distinct temperatures we had, and for each temperature, how many times it was repeated in the period. We say that the grapevine has quality x if we have at least x distinct temperatures that were repeated in x days during the growth of its grapes.

Your task is to compute the quality of production of each grapevine in the vineyard. You are given the temperatures measured in N days in the vineyard. Next, for each one of the Q grapevines in the vineyard, you are given the start and end days of their growth periods. For each one of these grapevines, you must compute the maximum quality of their production.
*/
#include<bits/stdc++.h>
using namespace std;

//-----
#define x first
#define y second
#define len(x) ((int) (x).size())
using pii = pair<int, int>;
using ll = long long;
using llu = long long unsigned;
using ld = long double;

const ld EPS = 1e-9;
int cmp (ld x, ld y = 0, ld tol = EPS) {
  return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int MOD = 1;
int mod (ll x, ll m = MOD) {
  return ((x%m) + m)%m;
}

//--------------------

const int NQ = 3e4 + 10, SQN = 175;

int n, q;
int a[NQ];

struct Mo{
	int l, r, i;
	
	bool operator < (Mo &oth) const{
		int cur_block = l/SQN;
		if(cur_block == oth.l/SQN){
			if(cur_block%2 == 0) return (r < oth.r);
			return (r > oth.r);
		}
		return (cur_block < oth.l/SQN);
	};
} qry[NQ];

int ans[NQ];
int curL, curR = -1;
int freq[NQ];

int seg[4*NQ];

void add(int idx, int l, int r, int pos, int val){
	if(l == r){
		seg[idx] += val;
		return;
	}
	
	int mid = (l + r)/2;
	if(pos <= mid) add(2*idx + 1, l, mid, pos, val);
	else add(2*idx + 2, mid + 1, r, pos, val);
	
	seg[idx] = seg[2*idx + 1] + seg[2*idx + 2];
}

int query(int idx, int l, int r, int suff = 0){
	if(l == r){
		suff += seg[idx];
		return l;
	}
	
	int mid = (l + r)/2;
	
	if(seg[2*idx + 2] + suff >= mid + 1) return query(2*idx + 2, mid + 1, r, suff);
	
	return query(2*idx + 1, l, mid, suff + seg[2*idx + 2]);
}

void add(int pos){
	int val = a[pos];
	
	if(freq[val] > 0) add(0, 1, n, freq[val], -1);
	
	freq[val]++;
	
	add(0, 1, n, freq[val], 1);
}

void rmv(int pos){
	int val = a[pos];
	
	add(0, 1, n, freq[val], -1);
	
	freq[val]--;
	
	if(freq[val] > 0) add(0, 1, n, freq[val], 1);
}

int main () {
	scanf("%d %d", &n, &q);
	vector<int> comp;
	for(int i = 0; i < n; i++){
		scanf("%d", &a[i]);
		comp.push_back(a[i]);
	}
	sort(comp.begin(), comp.end());
	comp.resize(unique(comp.begin(), comp.end()) - comp.begin());
	for(int i = 0; i < n; i++){
		a[i] = lower_bound(comp.begin(), comp.end(), a[i]) - comp.begin();
	}
	
	for(int i = 0; i < q; i++){
		int l, r;
		scanf("%d %d", &l, &r); l--, r--;
		qry[i] = {l, r, i};
	}
	sort(qry, qry + q);
	
	for(int i = 0; i < q; i++){
		int l = qry[i].l, r = qry[i].r, idx = qry[i].i;
		
		while(curR < r) add(++curR);
		while(curL > l) add(--curL);
		while(curR > r) rmv(curR--);
		while(curL < l) rmv(curL++);
		
		ans[idx] = query(0, 1, n);
	}
	
	for(int i = 0; i < q; i++){
		printf("%d\n", ans[i]);
	}
	
	return 0;
}
