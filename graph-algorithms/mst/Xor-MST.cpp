/*
You are given a complete undirected graph with n vertices. A number ai is assigned to each vertex, and the weight of an edge between vertices i and j is equal to ai xor aj.

Calculate the weight of the minimum spanning tree in this graph.

Input
The first line contains n (1 ≤ n ≤ 200000) — the number of vertices in the graph.

The second line contains n integers a1, a2, ..., an (0 ≤ ai < 2^30) — the numbers assigned to the vertices.
*/
#include <bits/stdc++.h>
using namespace std;
#define len(x) ((int)(x).size())

const int N = 2e5 + 10;

int a[N];

struct Trie{
	struct Node{
		Node *child[2];
		int cnt;
		
		Node(): child{NULL, NULL}, cnt(0){}
	} *root;
	
	Trie(): root(NULL){}
	
	void add(int x){
		if(!root) root = new Node();
		Node *node = root;
		for(int i = 29; i >= 0; i--){
			bool bit = (x & (1 << i));
			if(!node->child[bit]) node->child[bit] = new Node();
			node = node->child[bit];
			node->cnt++;
		}
	}
	
	void rmv(int x){
		Node *node = root;
		for(int i = 29; i >= 0; i--){
			bool bit = (x & (1 << i));
			node = node->child[bit];
			node->cnt--;
		}
	}
	
	int minxor(int x){
		int ret = 0;
		Node *node = root;
		for(int i = 29; i >= 0; i--){
			bool bit = (x & (1 << i));
			if(node->child[bit] && node->child[bit]->cnt) node = node->child[bit];
			else node = node->child[!bit], ret |= (1 << i);
		}
		return ret;
	}
} trie;

long long solve(int l, int r, int pos = 29){
	if(l >= r || pos == -1) return 0;
	int mid = l - 1;
	for(int i = l; i <= r; i++){
		if(!(a[i] & (1 << pos))) swap(a[++mid], a[i]);
	}
	int cur = 0;
	if(l <= mid && mid < r){
		cur = INT_MAX;
		for(int i = l; i <= mid; i++) trie.add(a[i]);
		for(int i = mid + 1; i <= r; i++) cur = min(cur, trie.minxor(a[i]));
		for(int i = l; i <= mid; i++) trie.rmv(a[i]);
	}
	return cur + solve(l, mid, pos - 1) + solve(mid + 1, r, pos - 1);
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	printf("%lld\n", solve(0, n - 1));
	return 0;
}
