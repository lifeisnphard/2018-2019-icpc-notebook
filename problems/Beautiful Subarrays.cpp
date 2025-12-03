/*
One day, ZS the Coder wrote down an array of integers a with elements a1,  a2,  ...,  an.

A subarray of the array a is a sequence al,  al  +  1,  ...,  ar for some integers (l,  r) such that 1  ≤  l  ≤  r  ≤  n. ZS the Coder thinks that a subarray of a is beautiful if the bitwise xor of all the elements in the subarray is at least k.

Help ZS the Coder find the number of beautiful subarrays of a!

Input
The first line contains two integers n and k (1 ≤ n ≤ 10^6, 1 ≤ k ≤ 10^9) — the number of elements in the array a and the value of the parameter k.

The second line contains n integers ai (0 ≤ ai ≤ 10^9) — the elements of the array a.
*/
#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
#define x first
#define y second
using namespace std;

struct Trie{
	struct Node{
		int qtd;
		Node *child[2];
		
		Node(): qtd(0), child{NULL, NULL}{}
	} *root;
	
	Trie(): root(new Node()){}
	
	void add(int x){
		Node *node = root;
		for(int i = 29; i >= 0; i--){
			bool bit = x & (1 << i);
			if(!node->child[bit]) node->child[bit] = new Node();
			node = node->child[bit];
			node->qtd++;
		}
	}
	
	int count(int x, int k){
		int ret = 0;
		Node *node = root;
		for(int i = 29; i >= 0; i--){
			bool bx = x & (1 << i), bk = k & (1 << i);
			if(bk){
				if(!node->child[!bx]) return ret;
				node = node->child[!bx];
			}else{
				if(node->child[!bx]) ret += node->child[!bx]->qtd;
				if(!node->child[bx]) return ret;
				node = node->child[bx];
			}
		}
		return ret + node->qtd;
	}
} trie;

int main(){
	int n, k, cur = 0;
	scanf("%d %d", &n, &k);
	trie.add(0);
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		int x;
		scanf("%d", &x);
		cur ^= x;
		ans += trie.count(cur, k);
		trie.add(cur);
	}
	printf("%lld\n", ans);
	return 0;
}
