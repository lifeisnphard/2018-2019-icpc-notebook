#include <bits/stdc++.h>

using namespace std;

#define len(x) ((int)(x).size())
#define x first
#define y second

using ll = long long;
using llu = unsigned long long;
using ld = long double;

inline int mod (ll x, int m) {
  return (int)(((x%m) + m)%m);
}

ll gcd(ll a, ll b){
	while(b) a %= b, swap(a, b);
	return abs(a);
}

// a and b must be positive
ll ext_gcd(ll a, ll b, ll &x, ll &y){
	if(b == 0){
		x = 1, y = 0;
		return a;
	}
	ll d = ext_gcd(b, a%b, x, y);
	x -= a/b*y, swap(x, y);
	return d;
}

// a and b must be non-zero
ll diophantine(ll a, ll b, ll c, ll &x, ll &y){
	ll g = ext_gcd(abs(a), abs(b), x, y);
	if(c%g != 0) return 0;
	
	if(a < 0) x *= -1;
	if(b < 0) y *= -1;
	
	x *= c/g, y *= c/g;
	// (x + k*(b/g), y - k*(a/g)) is solution if k integer
	return g;
}

ll get_inv(ll a, ll m){
	ll x, y;
	if(!diophantine(a, m, 1, x, y)) return -1;
	return mod(x, m);
}

int main(){
	int n;
	scanf("%d", &n);
	vector<int> val(n);
	for(int i = 0; i < n; i++){
		scanf("%d", &val[i]);
	}
	int t, a, b;
	scanf("%d %d %d", &t, &a, &b);
	
	int inv = get_inv(a, t);
	
	if(inv == -1){
		printf("DECIFRAGEM AMBIGUA\n");
		return 0;
	}
	
	for(int i = 0; i < n; i++){
		val[i] = (val[i] - b)%t;
		if(val[i] < 0) val[i] += t;
		
		if(i > 0) printf(" ");
		printf("%d", val[i]*1LL*inv%t);
	}
	printf("\n");
	return 0;
}
