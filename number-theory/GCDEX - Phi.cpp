/*
Given the value of N, you will have to find the value of G. The meaning of G is given in the following code

G = 0;
for (i = 1; i < N; i++)
  for (j = i+1; j <= N; j++) 
    G += gcd(i, j);
Here gcd() is a function that finds the greatest common divisor of the two input numbers.
Input
The input file contains at most 20000 lines of inputs. Each line contains an integer N (1 < N < 1000001). The meaning of N is given in the problem statement. Input is terminated by a line containing a single zero.
*/
#include <bits/stdc++.h>
#define len(o) ((int)(o).size())
#define get(o, i) get<i>(o)
#define x first
#define y second
using namespace std;

const int N = 1e6 + 10;

int phi[N];
long long ans[N];

int main(){
	for(int i = 1; i <= 1e6; i++){
		phi[i] = i;
	}
	for(int i = 1; i <= 1e6; i++){
		for(int j = 2*i; j <= 1e6; j += i){
			phi[j] -= phi[i];
		}
	}
	for(int i = 1; i <= 1e6; i++){
		for(int j = i; j <= 1e6; j += i){
			ans[j] += (j/i)*1LL*phi[i];
		}
	}
	for(int i = 1; i <= 1e6; i++){
		ans[i] -= i;
		ans[i] += ans[i - 1];
	}
	int n;
	while(scanf("%d", &n) && n){
		printf("%lld\n", ans[n]);
	}
	return 0;
}
