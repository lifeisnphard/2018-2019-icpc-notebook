#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define len(x) ((int)(x).size())
#define x first
#define y second

using ll = long long;
using llu = unsigned long long;
using ld = long double;

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const ld EPS = 1e-9;
inline int cmp(ld x, ld y = 0, ld tol = EPS) {
  return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int MOD = 1;
inline int mod(ll x, int m = MOD){
  return (int)(((x%m) + m)%m);
}

ll gcd(ll a, ll b){
	while(b) a %= b, swap(a, b);
	return abs(a);
}

ll lcm(ll a, ll b){
	return abs(a*b)/gcd(a, b);
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

ll get_inv(ll a, ll m = MOD){
	ll x, y;
	if(!diophantine(a, m, 1, x, y)) return -1;
	return mod(x, m);
}

ll modpow(ll a, ll x, ll m = MOD){
	if(x < 0) return inv(modpow(a, -x, m), m);
	
	ll ret = 1;
	while(x){
		if(x & 1) ret = mod(ret*a, m);
		a = mod(a*a, m), x >>= 1;
	}
	return ret;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
	//
	return 0;
}
