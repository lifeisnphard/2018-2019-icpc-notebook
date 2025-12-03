/*
In this problem, you have to maintain a dynamic set of numbers which support the two fundamental operations

INSERT(S,x): if x is not in S, insert x into S
DELETE(S,x): if x is in S, delete x from S
and the two type of queries

K-TH(S) : return the k-th smallest element of S
COUNT(S,x): return the number of elements of S smaller than x
*/
#include <bits/stdc++.h>
using namespace std;

struct Treap{
	struct Node{
		int val, prio, qtd;
		Node *L, *R;
		
		Node(){}
		Node(int val): val(val), prio(rand()), qtd(1), L(NULL), R(NULL){}
	} *root;

	Treap(): root(NULL){ srand(time(NULL)); }

	int qtd(Node *node){
		return node? node->qtd : 0;
	}

	void upd(Node *node){
		if(!node) return;
		node->qtd = qtd(node->L) + 1 + qtd(node->R);
	}

	Node *merge(Node *a, Node *b){
		if(!a) return b;
		if(!b) return a;

		if(a->prio >= b->prio){
			a->R = merge(a->R, b);
			upd(a);
			return a;
		}else{
			b->L = merge(a, b->L);
			upd(b);
			return b;
		}
	}

	void split(Node *node, int val, Node *&a, Node *&b){
		if(!node){
			a = b = NULL;
			return;
		}

		Node *tmp;
		if(node->val <= val){
			split(node->R, val, tmp, b);
			a = node;
			a->R = tmp;
			upd(a);
		}else{
			split(node->L, val, a, tmp);
			b = node;
			b->L = tmp;
			upd(b);
		}
	}

	void insert(int val){
		Node *a, *b;
		split(root, val, a, b);
		root = merge(merge(a, new Node(val)), b);
	}

	void erase(int val){
		Node *a, *b, *c;
		split(root, val, a, c);
		split(a, val - 1, a, b);
		
		root = merge(a, c);
		delete b;
		b = NULL;
	}

	int count(int val){
		Node *a, *b;
		split(root, val - 1, a, b);
		int ret = qtd(a);
		root = merge(a, b);
		return ret;
	}

	int kth(Node *node, int k){
		int pos = qtd(node->L) + 1;
		if(pos == k) return node->val;
		if(pos > k) return kth(node->L, k);
		return kth(node->R, k - pos);
	}

	int kth(int k){
		return kth(root, k);
	}
} treap;

int main(){
	int q;
	scanf("%d", &q);
	unordered_map<int, bool> has;
	while(q--){
		char type; int x;
		scanf(" %c %d", &type, &x);
		if(type == 'I'){
			if(!has[x]){
				has[x] = true;
				treap.insert(x);
			}
		}else if(type == 'D'){
			if(has[x]){
				has[x] = false;
				treap.erase(x);
			}
		}else if(type == 'K'){
			if(x <= treap.qtd(treap.root)) printf("%d\n", treap.kth(x));
			else printf("invalid\n");
		}else{
			printf("%d\n", treap.count(x));
		}
	}
	return 0;
}
