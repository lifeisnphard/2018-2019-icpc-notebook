/*
You are given an array a consisting of n integers. You have to process q queries to this array; each query is given as four numbers l, r, x and y, denoting that for every i such that l ≤ i ≤ r and ai = x you have to set ai equal to y.

Print the array after all queries are processed.
*/
#include <bits/stdc++.h>
using namespace std;
#define len(x) ((int)(x).size())

const int N = 2e5 + 10, SQN = 450, C = 110;

list<int> pos[SQN][C];
int ans[N];

void modify(int idx, int l, int r, int x, int y){
	auto it = pos[idx][x].begin();
	while(it != pos[idx][x].end()){
		auto nxt = next(it);
		if(*it >= l && *it <= r){
			pos[idx][y].splice(pos[idx][y].begin(), pos[idx][x], it);
		}
		it = nxt;
	}
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int a;
		scanf("%d", &a);
		pos[i/SQN][a].push_back(i);
	}
	int q;
	scanf("%d", &q);
	while(q--){
		int l, r, x, y;
		scanf("%d %d %d %d", &l, &r, &x, &y); l--, r--;
		if(x == y) continue;
		int bl = l/SQN, br = r/SQN;
		modify(bl, l, r, x, y);
		if(bl != br){
			for(int i = bl + 1; i < br; i++){
				pos[i][y].splice(pos[i][y].begin(), pos[i][x]);
			}
			modify(br, l, r, x, y);
		}
	}
	for(int i = 0; i < SQN; i++){
		for(int j = 1; j <= 100; j++){
			for(auto p : pos[i][j]){
				ans[p] = j;
			}
		}
	}
	for(int i = 0; i < n; i++){
		printf("%d ", ans[i]);
	}
	printf("\n");
	return 0;
}
