/*
T test cases. Given an integer n (1 <= n <= 10^6). Compute the value of the totient.
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;

int phi[N];
bool is_composite[N];

void sieve () {
	std::fill (is_composite, is_composite + N, false);
	
	phi[1] = 1;
	std::vector <int> prime;
	for (int i = 2; i < N; ++i) {
		if (!is_composite[i]) {
			prime.push_back (i);
			phi[i] = i - 1;					//i is prime
		}
		for (int j = 0; j < prime.size (); ++j) {
			if(i * prime[j] >= N) break;
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];	//prime[j] divides i
				break;
			} else {
				phi[i * prime[j]] = phi[i] * phi[prime[j]];	//prime[j] does not divide i
			}
		}
	}
}

int main(){
    sieve();

    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        printf("%d\n", phi[n]);
    }
    return 0;
}
