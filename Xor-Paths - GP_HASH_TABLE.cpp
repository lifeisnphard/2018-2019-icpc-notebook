/*
Number of paths in a grid using only right and bottom moves such that the xor of the elements in the path is exactly k. (n, m <= 20 and k <= 10^18).

gp_hash_table with custom hash function (necessary because the standard function uses powers of 2).
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define len(x) ((int)(x).size())
#define x first
#define y second

using ll = long long;
using llu = unsigned long long;
using lld = long double;

const int NM = 25;

int n, m;
ll k, a[NM][NM];

// one option for custom hash function
const ll TIME = chrono::high_resolution_clock::now().time_since_epoch().count();
const ll SEED = (ll)(new ll);
const ll RANDOM = TIME ^ SEED;
const ll MOD = (int)1e9+7;
const ll MUL = (int)1e6+3;

struct chash{
    ll operator()(ll x) const { return std::hash<ll>{}((x ^ RANDOM) % MOD * MUL); }
};

/*
// another option
unsigned hash_f(unsigned x) {
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x;
}
struct chash {
	int operator()(int x) const { return hash_f(x); }
};
*/

gp_hash_table<ll, int, chash> mp[NM][NM];

void right_bottom(int i, int j, int tot, ll mask = 0){
	if(i >= n || j >= m) return;

	mask ^= a[i][j];
	if(i + j == tot){
		mp[i][j][mask]++;
		return;
	}
	right_bottom(i + 1, j, tot, mask);
	right_bottom(i, j + 1, tot, mask);
}

ll left_up(int i, int j, int tot, ll mask = 0){
	if(i < 0 || j < 0) return 0;
	
	if(n + m - i - j - 2 == tot){
		if(mp[i][j].find(k ^ mask) == mp[i][j].end()) return 0;
		return mp[i][j][k ^ mask];
	}
	mask ^= a[i][j];
	return left_up(i - 1, j, tot, mask) + left_up(i, j - 1, tot, mask);
}

int main(){
	scanf("%d %d %lld", &n, &m, &k);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			scanf("%lld", &a[i][j]);
		}
	}
	int total_len = n + m - 2;
	right_bottom(0, 0, total_len/2);
	printf("%lld\n", left_up(n - 1, m - 1, total_len - total_len/2));
	
	return 0;
}
