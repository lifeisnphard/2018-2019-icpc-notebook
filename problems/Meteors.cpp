/*
There are N member states and M sectors. Each sector is owned by a member state. There are Q queries, each of which denote the amount of meteor shower in a [L, R] range of sectors on that day. The ith member state wants to collect reqd[i] meteors over all its sectors. For every member state, what is the minimum number of days it would have to wait to collect atleast the required amount of meteors?
*/
#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
#define x first
#define y second
using namespace std;

const int NMK = 3e5 + 10;

int n, m, k;
vector<int> pos[NMK];
int need[NMK], L[NMK], R[NMK];
pair<pair<int, int>, int> upd[NMK];

long long bit[NMK];

void reset(){
	for(int i = 1; i <= m; i++){
		bit[i] = 0;
	}
}

void add(int pos, int val){
	for(int i = pos; i <= m; i += (i & -i)){
		bit[i] += val;
	}
}

void add_range(int l, int r, int val){
	add(l, val);
	add(r + 1, -val);
}

long long get_val(int pos){
	long long ret = 0;
	for(int i = pos; i >= 1; i -= (i & -i)){
		ret += bit[i];
	}
	return ret;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++){
		int x;
		scanf("%d", &x);
		pos[x].push_back(i);
	}
	for(int i = 1; i <= n; i++){
		scanf("%d", &need[i]);
	}
	scanf("%d", &k);
	for(int i = 1; i <= k; i++){
		scanf("%d %d %d", &upd[i].x.x, &upd[i].x.y, &upd[i].y);
	}
	for(int i = 1; i <= n; i++){
		L[i] = 1, R[i] = k + 1;
	}
	while(1){
		reset();
		int cnt = 0;
		vector<vector<int>> in(k + 1);
		for(int i = 1; i <= n; i++){
			if(L[i] < R[i]){
				in[(L[i] + R[i])/2].push_back(i);
				cnt++;
			}
		}
		if(!cnt) break;
		for(int i = 1; i <= k; i++){
			int l = upd[i].x.x, r = upd[i].x.y, a = upd[i].y;
			if(l <= r) add_range(l, r, a);
			else add_range(1, r, a), add_range(l, m, a);
			
			for(int state : in[i]){
				unsigned long long sum = 0;
				for(int x : pos[state]) sum += get_val(x);
				if(sum >= need[state]) R[state] = i;
				else L[state] = i + 1;
			}
		}
	}
	for(int i = 1; i <= n; i++){
		if(L[i] <= k) printf("%d\n", L[i]);
		else printf("NIE\n");
	}
	return 0;
}
