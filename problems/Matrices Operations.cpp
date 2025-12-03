#include <bits/stdc++.h>
#define len(o) ((int)(o).size())
#define get(o, i) get<i>(o)
#define x first
#define y second
using namespace std;

const int MOD = 1e9 + 7;

typedef vector<int> row;
typedef vector<row> matrix;

matrix operator * (matrix &a, matrix &b){
	assert(len(a) && len(a[0]) == len(b));
	
	int n = len(a), m = len(b[0]);
	matrix ret = matrix(n, row(m));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			for(int k = 0; k < len(b); k++){
				ret[i][j] = (ret[i][j] + a[i][k]*1LL*b[k][j])%MOD;
			}
		}
	}
	return ret;
}

void operator *= (matrix &a, matrix &b){
	a = a*b;
}

matrix powmod(matrix a, long long x){
	int n = len(a);
	assert(n == len(a[0]));
	matrix ret(n, row(n));
	for(int i = 0; i < n; i++)
		ret[i][i] = 1;
	while(x){
		if(x & 1) ret *= a;
		a *= a, x >>= 1;
	}
	return ret;
}

int main(){
	int n = 10;
	
	matrix t(2, row(2));
	t[0][0] = 0, t[0][1] = 1;
	t[1][0] = 1, t[1][1] = 1; // f(n) = (1)*f(n - 2) + (1)*f(n - 1)
	
	t = powmod(t, n - 1);
	
	matrix f(2, row(1));
	f[0][0] = 0; // f(0)
	f[1][0] = 1; // f(1)
	
	f = t*f;
	
	cout << f[0][0] << endl; // f(n - 1)
	cout << f[1][0] << endl; // f(n)
	
	return 0;
}
