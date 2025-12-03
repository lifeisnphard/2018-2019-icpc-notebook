/*
Lucas really wanted to create an interesting problem with strings, but he spent so much time thinking that ended up with no creativity to create a better statement for this problem.

The problem he came up with is the following:

Given and array v of strings, answer these queries:

1. update(i, s) replace the i-th position in the array with the a string s.
2. vprefix(l, r, s) check whether there is any string in sub-array [l, r] which is a prefix of s.
3. sprefix(l, r, s) check whether s is prefix of any string in sub-array [l, r].

-
This solution gave MLE but still can be useful for other problems
*/
#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int N = 1e5 + 10;

struct Node{
	int cnt;
	short fin;
	Node *child[26];
} *root[4*N];

void add(Node *&node, string &s, int i){
	if(node == NULL) node = new Node();
	
	node->cnt++;
	if(i == len(s)){
		node->fin++;
		return;
	}
	
	int c = s[i] - 'a';
	add(node->child[c], s, i + 1);
}

void rmv(Node *&node, string &s, int i){
	assert(node != NULL);
	
	node->cnt--;
	if(i < len(s)){
		int c = s[i] - 'a';
		rmv(node->child[c], s, i + 1);
	}else{
		node->fin--;
	}
	if(!node->cnt){
		delete node;
		node = NULL;
	}
}

bool vprefix(Node *node, string &s, int i){ // tem string na trie que é prefixo de s?
	if(node == NULL) return false;
	if(node->fin) return true;
	if(i == len(s)) return false;
	
	return vprefix(node->child[s[i] - 'a'], s, i + 1);
}

bool sprefix(Node *node, string &s, int i){ // s é prefixo de alguma string na trie?
	if(node == NULL) return false;
	if(i == len(s)) return true;
	
	return sprefix(node->child[s[i] - 'a'], s, i + 1);
}

string s[N], tmp;

void add(int idx, int l, int r, int pos, string &s, int sign){
	if(l != r){
		int mid = (l + r)/2;
		if(pos <= mid) add(2*idx + 1, l, mid, pos, s, sign);
		else add(2*idx + 2, mid + 1, r, pos, s, sign);
	}
	if(sign == 1) add(root[idx], s, 0);
	else rmv(root[idx], s, 0);
}

bool vprefix(int idx, int l, int r, int a, int b, string &s){
	if(l > b || r < a) return false;
	if(l >= a && r <= b) return vprefix(root[idx], s, 0);
	
	int mid = (l + r)/2;
	return vprefix(2*idx + 1, l, mid, a, b, s) || vprefix(2*idx + 2, mid + 1, r, a, b, s);
}

bool sprefix(int idx, int l, int r, int a, int b, string &s){
	if(l > b || r < a) return false;
	if(l >= a && r <= b) return sprefix(root[idx], s, 0);
	
	int mid = (l + r)/2;
	return sprefix(2*idx + 1, l, mid, a, b, s) || sprefix(2*idx + 2, mid + 1, r, a, b, s);
}

int main(){
	//freopen("in.txt", "r", stdin);
	
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		cin >> s[i];
		add(0, 1, n, i, s[i], 1);
	}
	int q;
	scanf("%d", &q);
	while(q--){
		int t;
		scanf("%d", &t);
		if(t == 1){
			int i;
			scanf("%d", &i);
			add(0, 1, n, i, s[i], -1);
			cin >> s[i];
			add(0, 1, n, i, s[i], 1);
		}else if(t == 2){
			int l, r;
			scanf("%d %d", &l, &r);
			cin >> tmp;
			printf("%c\n", vprefix(0, 1, n, l, r, tmp)? 'Y' : 'N');
		}else{
			int l, r;
			scanf("%d %d", &l, &r);
			cin >> tmp;
			printf("%c\n", sprefix(0, 1, n, l, r, tmp)? 'Y' : 'N');
		}
	}
	return 0;
}
