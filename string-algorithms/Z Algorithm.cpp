#include <bits/stdc++.h>
#define len(o) ((int)(o).size())
#define get(o, i) get<i>(o)
#define x first
#define y second
using namespace std;

const int N = 1e6 + 10;

int z[N];

void build(string p){
	int l = 0, r = 0;
	for(int i = 1; i < len(p); i++){
		if(i <= r) z[i] = min(r - i + 1, z[i - l]);
		while(z[i] + i < len(p) && p[z[i]] == p[z[i] + i]) z[i]++;
		if(r < i + z[i] - 1) l = i, r = i + z[i] - 1;
	}
}


int main(){
	//
	return 0;
}

