#include <bits/stdc++.h>
#define len(o) ((int)(o).size())
#define get(o, i) get<i>(o)
#define x first
#define y second
using namespace std;

const int N = 1e6 + 10;

int kmp[N];

void build_kmp(string p){
	int k = kmp[0] = -1;
	for(int i = 1; i < len(p); i++){
		while(k >= 0 && p[k + 1] != p[i]) k = kmp[k];
		if(p[k + 1] == p[i]) k++;
		kmp[i] = k;
	}
}

void run_kmp(string p, string t){
	int k = -1;
	for(int i = 0; i < len(t); i++){
		while(k >= 0 && p[k + 1] != t[i]) k = kmp[k];
		if(p[k + 1] == t[i]) k++;
		if(k + 1 == len(p)){
			printf("match terminando em %d\n", i);
			k = kmp[k];
		}
	}
}

int main(){
	string p;
	cin >> p;
	build_kmp(p);
	string t;
	cin >> t;
	run_kmp(p, t);
	return 0;
}
