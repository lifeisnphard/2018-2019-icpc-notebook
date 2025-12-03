/*
A organização da IOI está monitorando a fila e pediu que você faça um programa que inicialmente receba a descrição da fila inicial (número N de pessoas e suas alturas A1, A2, ... , AN, pela ordem na fila, onde A1 é a altura do primeiro da fila). Em seguida, seu programa deve processar dois tipos de operações:

na operação tipo 0, seu programa recebe a informação que um novo competidor, de altura H, acabou de entrar na fila, exatamente atrás do I-ésimo competidor na fila (para I = 0 o novo competidor entrou no começo da fila)
na operação tipo 1, seu programa recebe dois inteiros, I e D, e deve responder a uma consulta: considere a I-ésima pessoa na fila, digamos, P, e determine a posição na fila da pessoa mais próxima de P que está à frente de P e cuja altura é maior do que HI + D (onde HI é a altura de P).
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define mp make_pair

int bigRand(){ return ((rand() << 16) ^ rand()); }

struct Treap{
    struct Node{
        int val, prio, sz, ans;
        Node *l, *r;

        Node(){}
        Node(int val): val(val), prio(bigRand()), sz(1), ans(val), l(NULL), r(NULL){}
    } *root;

    Treap(): root(NULL){ srand(time(NULL)); }

    int count(Node *node){
        return ((node == NULL)? 0 : node->sz);
    }

    void upd_sz(Node *&node){
        if(node == NULL) return;
        node->sz = count(node->l) + 1 + count(node->r);
    }

    int ans(Node *node){
        return ((node == NULL)? 0 : node->ans);
    }

    void upd_ans(Node *&node){
        if(node == NULL) return;
        node->ans = max(node->val, max(ans(node->l), ans(node->r)));
    }

    Node* merge(Node *L, Node *R){
        if(L == NULL) return R;
        if(R == NULL) return L;

        if(L->prio > R->prio){
            L->r = merge(L->r, R);
            upd_sz(L), upd_ans(L);
            return L;
        }else{
            R->l = merge(L, R->l);
            upd_sz(R), upd_ans(R);
            return R;
        }
    }

    void split(Node *node, int pos, Node *&a, Node *&b){
        if(node == NULL){
            a = b = NULL;
            return;
        }
        if(count(node->l) <= pos){
            split(node->r, pos - count(node->l) - 1, node->r, b);
            a = node;
            upd_sz(a), upd_ans(a);
        }else{
            split(node->l, pos, a, node->l);
            b = node;
            upd_sz(b), upd_ans(b);
        }
    }

    void push_back(int val){
        root = merge(root, new Node(val));
    }

    void insert(int pos, int val){
        Node *L, *R;
        split(root, pos, L, R);
        root = merge(merge(L, new Node(val)), R);
    }

    int solve(Node *node, int val){
        if(node == NULL) return -1;

        if(node->r != NULL && ans(node->r) > val){
            int pos = solve(node->r, val);
            if(pos == -1) return -1;
            return count(node->l) + 1 + pos;
        }
        if(node->val > val){
            return count(node->l);
        }
        if(node->l != NULL && ans(node->l) > val){
            return solve(node->l, val);
        }
        return -1;
    }

    int query(int pos, int d){
        Node *L, *M, *R;
        split(root, pos, L, R);
        split(L, pos - 1, L, M);
        int ret = solve(L, M->val + d);
        root = merge(merge(L, M), R);
        return ret;
    }
} treap;

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
        treap.push_back(x);
	}

	int q;
	scanf("%d", &q);
	for(int k = 0; k < q; k++){
		int t, i, x;
		scanf("%d %d %d", &t, &i, &x);
		if(t == 0){
			treap.insert(i - 1, x);
		}else{
			printf("%d\n", 1 + treap.query(i - 1, x));
		}
	}

	return 0;
}
