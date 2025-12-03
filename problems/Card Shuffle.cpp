/*
Chef is organizing an online card game tournament and for this purpose he has to provide a card shuffling software. This software has to simulate the following shuffling process. A stack of N cards is placed face down on the table. Cards in the stack are ordered by value. Topmost card has value 1 and the one on the bottom has value N. To shuffle the cards we repeat the following steps M times:

1. take A cards from the top of the deck.
2. take another B cards from the top of the deck.
3. put the A cards, which you removed in the first step, back on top of the remaining deck.
4. take C cards from the deck
5. put the B cards, which you're still holding from the second move, card by card on top of the deck.
6. finally, return the block of C cards on top

Note: taking a block of cards from the top of the deck does not change their order. The entire block is removed in a single move and not card by card. The only exception is the fifth move, where you return cards one by one from the top.
*/
#include <bits/stdc++.h>
using namespace std;

int bigRand(){ return ((rand() << 16) ^ rand()); }

struct Treap{
    struct Node{
        int val, prio, len;
        bool lazy;
        Node *l, *r;

        Node(int val = 0): val(val), prio(bigRand()), len(1), lazy(false), l(NULL), r(NULL){}
    } *root;

    Treap(){ root = NULL; }

    int count(Node *node){ return (node == NULL)? 0 : node->len; }

    void upd(Node *node){
        if(node == NULL) return;
        node->len = 1 + count(node->l) + count(node->r);
        if(node->lazy){
            swap(node->l, node->r);
            if(node->l != NULL) node->l->lazy ^= 1;
            if(node->r != NULL) node->r->lazy ^= 1;
            node->lazy = false;
        }
    }

    Node* merge(Node *a, Node *b){
        if(a == NULL) return b;
        if(b == NULL) return a;

        upd(a), upd(b);
        if(a->prio > b->prio){
            a->r = merge(a->r, b);
            upd(a);
            return a;
        }else{
            b->l = merge(a, b->l);
            upd(b);
            return b;
        }
    }

    // Todas os elementos cuja posição é <= pos, deve ficar em a (0-indexed)
    void split(Node *node, Node *&a, Node *&b, int pos){
        if(node == NULL){
            a = b = NULL;
            return;
        }
        upd(node);
        if(count(node->l) <= pos){
            split(node->r, node->r, b, pos - count(node->l) - 1);
            a = node;
            upd(a);
        }else{
            split(node->l, a, node->l, pos);
            b = node;
            upd(b);
        }
    }

    void push_back(int val){ root = merge(root, new Node(val)); }

    void shuffle(int a, int b, int c){
        Node *A, *B, *C;
        // take A cards from the top of the deck.
        split(root, A, root, a);
        // take another B cards from the top of the deck.
        split(root, B, root, b);
        // put the A cards, which you removed in the first step, back on top of the remaining deck.
        root = merge(A, root);
        // take C cards from the deck
        split(root, C, root, c);
        // put the B cards, which you're still holding from the second move, card by card on top of the deck.
        B->lazy ^= 1;
        root = merge(B, root);
        // finally, return the block of C cards on top
        root = merge(C, root);
    }

    void print(Node *node){
        if(node == NULL) return;

        upd(node);
        print(node->l);
        printf("%d ", node->val);
        print(node->r);
    }
} cards;

int main(){
    srand(time(NULL));

    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        cards.push_back(i);
    }
    for(int i = 0, a, b, c; i < m; i++){
        scanf("%d %d %d", &a, &b, &c);
        cards.shuffle(a - 1, b - 1, c - 1);
    }
    cards.print(cards.root); printf("\n");
    return 0;
}
