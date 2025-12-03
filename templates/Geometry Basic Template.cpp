#include <bits/stdc++.h>

using namespace std;

#define len(x) ((int)(x).size())
#define x first
#define y second

using ll = long long;
using llu = unsigned long long;
using ld = long double;

struct point{
	ld x, y;
	
	point operator + (point b) const{ return {x + b.x, y + b.y}; }
	point operator - (point b) const{ return {x - b.x, y - b.y}; }
	point operator * (ld k) const{ return {x*k, y*k}; }
	point operator / (ld k) const{ return {x/k, y/k}; }
	
	ld operator * (point b) const{ return x*b.x + y*b.y; } // dot product
	ld operator | (point b) const{ return x*b.y - y*b.x; } // cross product
	
	bool operator == (point b) const{ return (x == b.x && y == b.y); }
	bool operator != (point b) const{ return !((*this) == b); }
	
	ld norm(){ return (*this)*(*this); } // squared size
	ld abs(){ return sqrt(norm()); } // size
	
	point rotate(ld a){ return {x*cosl(a) - y*sinl(a), x*sinl(a) + y*cosl(a)}; } // rotate by a rads counter-clockwise
	point perp(){ return {-y, x}; } // rotate PI/2 rads counter-clockwise
};

int main(){
	//
	return 0;
}
