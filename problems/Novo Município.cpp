#include <bits/stdc++.h>

using namespace std;

#define len(x) ((int)(x).size())
#define x first
#define y second

using ll = long long;
using llu = unsigned long long;
using ld = long double;

ll modmul(ll a, ll b, ll m){
	a %= m, b %= m;
	ll ret = 0;
	while(b){
		if(b & 1) ret = (ret + a)%m;
		a = 2*a%m, b >>= 1;
	}
	return ret;
}

ll modpow(ll a, ll x, ll m){
	a %= m;
	ll ret = 1;
	while(x){
		if(x & 1) ret = modmul(ret, a, m);
		a = modmul(a, a, m), x >>= 1;
	}
	return ret;
}

bool miller_rabin(ll n){
	vector<int> pr = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	
	for(int p : pr){
		if(n%p == 0) return n == p;
	}
	if(n < pr.back()) return false;
	
	ll s = 0, t = n - 1;
	while(~t & 1) t >>= 1, s++;
	
	for(int p : pr){
		ll pt = modpow(p, t, n);
		if(pt == 1) continue;
		
		bool ok = false;
		for(int j = 0; j < s; j++){
			if(pt == n - 1){
				ok = true;
				break;
			}
			pt = modmul(pt, pt, n);
		}
		if(!ok) return false;
	}
	
	return true;
}

ll gcd(ll a, ll b){
	while(b) a %= b, swap(a, b);
	return abs(a);
}

ll pollard_rho(ll n){
	if(~n & 1) return 2;
	
	ll x = rand()%(n - 2) + 2, y = x, c = rand()%(n - 1) + 1, d = 1;
	while(d == 1){
		x = (modmul(x, x, n) + c)%n;
		
		y = (modmul(y, y, n) + c)%n;
		y = (modmul(y, y, n) + c)%n;
		
		d = gcd(y - x, n);
		
		if(d == n) return pollard_rho(n);
	}
	return d;
}

int main(){
	srand(time(0));
	
	ll n;
	scanf("%lld", &n);
	if(n == 1 || miller_rabin(n)){
		printf("Nao\n");
	}else{
		printf("Sim\n");
		ll d = pollard_rho(n);
		printf("%lld %lld\n", d, n/d);
	}
	return 0;
}