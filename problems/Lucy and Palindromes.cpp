/*
There is a string of N latin letters. Lucy asks you to answer the following queries:

1 L R - reverse the substring from the L-th to the R-th character (1-indexed), inclusive.

2 L R - calculate the number of distinct palindromes that can be obtained by permutting characters from the L-th to the R-th in the arbitrary order (ignoring all other characters of the string).
*/
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair

typedef long long ll;

const int MOD = 1e9 + 7;
const int N = 1e5 + 10;

int fact[N], inv[N];

int powmod(int a, int x){
    if(x == 0) return 1;
    if(x%2 == 0){
        int half = powmod(a, x/2);
        return ((ll)half*half)%MOD;
    }
    return ((ll)a*powmod(a, x - 1))%MOD;
}

void pre(){
    fact[0] = 1, inv[0] = 1;
    for(int i = 1; i < N; i++){
        fact[i] = ((ll)i*fact[i - 1])%MOD;
        inv[i] = powmod(fact[i], MOD - 2);
    }
}

int bigRand(){ return ((rand() << 16) ^ rand()); }

struct Treap{
    struct Node{
        char val;
        int prio, qtd[10], len;
        bool lazy;
        Node *l, *r;

        Node(){}
        Node(char val): val(val), prio(bigRand()), len(1), lazy(false), l(NULL), r(NULL){
            for(int i = 0; i < 10; i++) qtd[i] = 0;
            qtd[val - 'a'] = 1;
        }
    } *root;

    Treap(): root(NULL){ srand(time(NULL)); }

    Node* newNode(char val){ return new Node(val); }

    int count(Node *node){ return ((node != NULL)? node->len : 0); }

    void upd_len(Node *&node){
        if(node == NULL) return;
        node->len = 1 + count(node->l) + count(node->r);
    }

    void upd_qtd(Node *&node){
        if(node == NULL) return;

        for(int i = 0; i < 10; i++){
            node->qtd[i] = 0;
            node->qtd[i] += (node->l != NULL)? node->l->qtd[i] : 0;
            node->qtd[i] += (node->r != NULL)? node->r->qtd[i] : 0;
        }
        node->qtd[node->val - 'a']++;
    }

    void lazy(Node *&node){
        if(node == NULL) return;
        if(node->lazy){
            node->lazy = false;
            swap(node->l, node->r);
            if(node->l != NULL) node->l->lazy ^= 1;
            if(node->r != NULL) node->r->lazy ^= 1;
        }
    }

    void split(Node *node, Node *&a, Node *&b, int pos){
        if(node == NULL){
            a = b = NULL;
            return;
        }

        lazy(node);
        if(count(node->l) <= pos){
            split(node->r, node->r, b, pos - count(node->l) - 1);
            a = node;
            upd_len(a);
            upd_qtd(a);
        }else{
            split(node->l, a, node->l, pos);
            b = node;
            upd_len(b);
            upd_qtd(b);
        }
    }

    Node* merge(Node *L, Node *R){
        if(L == NULL) return R;
        if(R == NULL) return L;

        lazy(L), lazy(R);
        if(L->prio > R->prio){
            L->r = merge(L->r, R);
            upd_len(L);
            upd_qtd(L);
            return L;
        }else{
            R->l = merge(L, R->l);
            upd_len(R);
            upd_qtd(R);
            return R;
        }
    }

    void push_back(char val){ root = merge(root, newNode(val)); }

    void print(Node *node){
        if(node == NULL) return;
        lazy(node);
        print(node->l);
        printf("%c", node->val);
        print(node->r);
    }

    void reverse(int x, int y){
        Node *L, *R, *M;
        split(root, M, R, y);
        split(M, L, M, x - 1);
        M->lazy ^= 1;
        root = merge(merge(L, M), R);
    }

    int ans(int x, int y){
        Node *L, *R, *M;
        split(root, M, R, y);
        split(M, L, M, x - 1);

        int qtd_odd = 0;
        for(int i = 0; i < 10; i++){
            if(M->qtd[i]%2 == 1) qtd_odd++;
        }
        int ans = 0;
        if(qtd_odd <= 1){
            ans = fact[(y - x + 1)/2];
            for(int i = 0; i < 10; i++){
                ans = ((ll)ans*inv[M->qtd[i]/2])%MOD;
            }
        }

        root = merge(merge(L, M), R);

        return ans;
    }
} treap;

int main(){
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
    #endif

    pre();

    int n, m;
    scanf("%d %d", &n, &m);
    char s[N];
    scanf("%s", &s);
    for(int i = 0; i < n; i++){
        treap.push_back(s[i]);
    }
    for(int i = 0; i < m; i++){
        int t, l, r;
        scanf("%d %d %d", &t, &l, &r);
        if(t == 1){
            treap.reverse(l - 1, r - 1);
        }else{
            printf("%d\n", treap.ans(l - 1, r - 1));
        }
    }

    return 0;
}
