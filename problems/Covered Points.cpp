/*
You are given n (1 <= n <= 1000) segments on a Cartesian plane. Each segment's endpoints have integer coordinates. Segments can intersect with each other. No two segments lie on the same line.

Count the number of distinct points with integer coordinates, which are covered by at least one segment.
*/
#include <bits/stdc++.h>
using namespace std;

////////////// Prewritten code follows. Look down for solution. ////////////////
#define x first
#define y second
#define len(x) ((int)(x).size())
using pii = pair<int, int>;
using ll = long long;
using llu = long long unsigned;
using ld = long double;

const ld EPS = 1e-9;
inline int cmp(ld x, ld y = 0, ld tol = EPS){
	return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int MOD = 1;
inline int mod(ll x, int m = MOD){
	return (int)(((x%m) + m)%m);
}

////////////////////////// Solution starts below. //////////////////////////////

const int N = 1010;

struct point{
	ll x, y;
	
	point(){}
	point(ll _x, ll _y): x(_x), y(_y){}
	
	bool operator < (point b) const{
		return make_pair(x, y) < make_pair(b.x, b.y);
	}
	
	point operator - (point b) const{
		return {x - b.x, y - b.y};
	}
	
 	ll operator * (point b){ // dot product
		return x*b.x + y*b.y;
	}
	
	ll operator & (point b) const{ // cross product
		return x*b.y - y*b.x;
	}
	
	point perp(){ // perpendicular vector to this one
		return {-y, x};
	}
};

struct line{ // ax + by = c
	point n;
	ll c;
	
	line(point p, point q): n((q - p).perp()), c(n*p){}
	
	bool parallel(line oth){
		return (n & oth.n) == 0;
	}
	
	point intersection(line oth){
		if(parallel(oth)) return {(ll)1e9, (ll)1e9}; // parallel lines
		
		ll den = n & oth.n;
		
		ll num_x = point(c, n.y) & point(oth.c, oth.n.y);
		ll num_y = point(n.x, c) & point(oth.n.x, oth.c);
		
		if(num_x%den != 0 || num_y%den != 0) return {(ll)1e9, (ll)1e9}; // no integer intersection
		
		return {num_x/den, num_y/den};
	}
};

int sign(ll x){
	return x < 0 ? -1 : (x > 0 ? 1 : 0);
}

struct segment{
	point p, q;
	
	bool intersect(segment oth){
		int sign1 = sign((oth.q - oth.p) & (q - oth.q));
		int sign2 = sign((oth.q - oth.p) & (p - oth.q));
		
		int sign3 = sign((q - p) & (oth.q - q));
		int sign4 = sign((q - p) & (oth.p - q));
		
		return sign1*sign2 <= 0 && sign3*sign4 <= 0;
	}
	
	point intersection(segment oth){
		if(!intersect(oth)) return {(ll)1e9, (ll)1e9}; // no intersection at all
		return line(p, q).intersection(line(oth.p, oth.q));
	}
} seg[N];

ll gcd(ll a, ll b){
	while(b) a %= b, swap(a, b);
	return abs(a);
}

int main(){
	int n;
	scanf("%d", &n);
	
	ll ans = 0;
	for(int i = 0; i < n; i++){
		point a, b;
		scanf("%lld %lld %lld %lld", &a.x, &a.y, &b.x, &b.y);
		ans += gcd(b.x - a.x, b.y - a.y) + 1;
		seg[i] = {a, b};
	}
	for(int i = 0; i < n; i++){
		set<point> s;
		for(int j = 0; j < i; j++){
			point go = seg[i].intersection(seg[j]);
			if(go.x != (ll)1e9) s.insert(go);
		}
		ans -= len(s);
	}
	
	printf("%lld\n", ans);
	
	return 0;
}