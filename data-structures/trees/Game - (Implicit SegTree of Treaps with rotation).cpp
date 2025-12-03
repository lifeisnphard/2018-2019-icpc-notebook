/*
Bazza and Shazza are playing a game. The board is a grid of cells, with R rows numbered 0, …, R - 1, and C columns, numbered 0, …, C - 1. We let (P, Q) denote the cell in row P and column Q. Each cell contains a non-negative integer, and at the beginning of the game all of these integers are zero.

The game proceeds as follows. At any time, Bazza may either:

update a cell (P, Q), by assigning the integer that it contains
ask Shazza to calculate the greatest common divisor (GCD) of all integers within a rectangular block of cells, with opposite corners (P, Q) and (U, V) inclusive.
Bazza will take NU + NQ actions (updating cells NU times and asking questions NQ times) before he gets bored and goes outside to play cricket.

Your task is to work out the correct answers.
R <= 10^9, C <= 10^9, Nu <= 22,000, Nq <= 250,000
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b){
    if(b == 0) return a;
    return gcd(b, a%b);
}

struct Treap{
    struct Node{
        ll val, ans;
        int pos, prio, lb, rb, count;
        Node *l, *r;

        Node(){}
        Node(int pos, ll val): val(val), ans(val), pos(pos), prio(rand()), lb(pos), rb(pos), count(1), l(NULL), r(NULL){}
    } *root;

    Treap(): root(NULL){ srand(time(NULL)); }

    int count(Node *node){ return (node == NULL)? 0 : node->count; }

    ll ans(Node *node){ return (node == NULL)? 0 : node->ans; }

    void upd(Node *&node){
        if(node == NULL) return;
        node->ans = gcd(node->val, gcd(ans(node->l), ans(node->r)));
        node->lb = (node->l == NULL)? node->pos : node->l->lb;
        node->rb = (node->r == NULL)? node->pos : node->r->rb;
        node->count = count(node->l) + 1 + count(node->r);
    }

    void modify(Node *&node, int pos, ll val){
        if(node == NULL){
            node = new Node(pos, val);
            return;
        }
        if(node->pos == pos){
            node->val = val;
        }else if(node->pos > pos){
            modify(node->l, pos, val);
            if(node->prio < node->l->prio){
                Node *tmp = node->l;
                node->l = tmp->r;
                tmp->r = node;
                node = tmp;
                upd(node->r);
            }
        }else{
            modify(node->r, pos, val);
            if(node->prio < node->r->prio){
                Node *tmp = node->r;
                node->r = tmp->l;
                tmp->l = node;
                node = tmp;
                upd(node->l);
            }
        }
        upd(node);
    }

    void modify(int pos, ll val){ modify(root, pos, val); }

    ll query(Node *node, int l, int r){
        if(node == NULL || node->lb > r || node->rb < l) return 0;
        if(node->lb >= l && node->rb <= r) return node->ans;
        ll ans = (node->pos >= l && node->pos <= r)? node->val : 0;
        return gcd(ans, gcd(query(node->l, l, r), query(node->r, l, r)));
    }

    ll query(int l, int r){ return query(root, l, r); }
};

struct Node{
    Node *l, *r;
    Treap *treap;

    Node(): l(NULL), r(NULL){ treap = new Treap(); }
} *root;

ll query(Node *node, int l, int r, int qlx, int qrx, int qly, int qry){
    if(node == NULL || l > qrx || r < qlx) return 0;
    if(l >= qlx && r <= qrx) return node->treap->query(qly, qry);
    int mid = (l + r)/2;
    return gcd(query(node->l, l, mid, qlx, qrx, qly, qry), query(node->r, mid + 1, r, qlx, qrx, qly, qry));
}

void modify(Node *&node, int l, int r, int px, int py, ll val){
    if(node == NULL) node = new Node();
    if(l == r){
        node->treap->modify(py, val);
    }else{
        int mid = (l + r)/2;
        if(px <= mid){
            modify(node->l, l, mid, px, py, val);
        }else{
            modify(node->r, mid + 1, r, px, py, val);
        }
        ll a = (node->l == NULL)? 0 : node->l->treap->query(py, py);
        ll b = (node->r == NULL)? 0 : node->r->treap->query(py, py);
        node->treap->modify(py, gcd(a, b));
    }
}

int main(){
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    for(int i = 0; i < q; i++){
        int t;
        scanf("%d", &t);
        if(t == 1){
            int x, y; ll val;
            scanf("%d %d %lld", &x, &y, &val);
            modify(root, 0, n - 1, x, y, val);
        }else{
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            printf("%lld\n", query(root, 0, n - 1, x1, x2, y1, y2));
        }
    }
    return 0;
}
