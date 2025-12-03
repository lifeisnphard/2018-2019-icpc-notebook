/*
Dada uma árvore com raiz que consiste de N vértices, onde cada vértice i tem um valor Vi.

Responder a M consultas: para um dado vértice X lhe dizer qual é o K-ésimo menor valor da subárvore com raiz no vértice X.
*/
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair

const int NM = 100100;

int n, a[NM], ans[NM];
vector<int> adj[NM];
int subsize[NM], sc[NM];
vector<pair<int, int> > qry[NM];

struct Treap{
    struct Node{
        int val, prio, len;
        Node *l, *r;

        Node(){}
        Node(int val): val(val), prio(rand()), len(1), l(NULL), r(NULL){}
    } *root;

    Treap(): root(NULL){ srand(time(NULL)); }

    Node* newNode(int val){ return new Node(val); }

    void clear(Node *&node){
        if(node == NULL) return;
        clear(node->l), clear(node->r);
        delete node;
        node = NULL;
    }

    void clear(){ clear(root); }

    void update(Node *&node){
        if(node == NULL) return;

        node->len = 1;
        if(node->l != NULL) node->len += node->l->len;
        if(node->r != NULL) node->len += node->r->len;
    }

    Node* merge(Node *L, Node *R){
        if(L == NULL) return R;
        if(R == NULL) return L;

        if(L->prio > R->prio){
            L->r = merge(L->r, R);
            update(L);
            return L;
        }else{
            R->l = merge(L, R->l);
            update(R);
            return R;
        }
    }

    void split(Node *node, int val, Node *&a, Node *&b){
        if(node == NULL){
            a = b = NULL;
            return;
        }

        Node *tmp;
        if(node->val <= val){
            split(node->r, val, tmp, b);
            a = node;
            a->r = tmp;
            update(a);
        }else{
            split(node->l, val, a, tmp);
            b = node;
            b->l = tmp;
            update(b);
        }
    }

    void insert(int val){
        Node *L, *R;
        split(root, val, L, R);
        root = merge(merge(L, newNode(val)), R);
    }

    void erase(Node *&node, int val){
        if(node == NULL) return;
        if(val < node->val) erase(node->l, val);
        if(val > node->val) erase(node->r, val);
        else node = merge(node->l, node->r);
        update(node);
    }

    void erase(int val){ erase(root, val); }

    int kth(Node *node, int k){
        int ql = (node->l != NULL)? node->l->len : 0;
        if(k == ql) return node->val;
        if(k < ql) return kth(node->l, k);
        return kth(node->r, k - ql - 1);
    }

    int kth(int k){ return kth(root, k - 1); }
} treap;

void dfs(int u, int p){
    subsize[u] = 1, sc[u] = -1;
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(v != p){
            dfs(v, u);
            subsize[u] += subsize[v];
            if(sc[u] == -1 || subsize[v] > subsize[sc[u]]){
                sc[u] = v;
            }
        }
    }
}

void addAll(int u, int p, int val){
    if(val == 1) treap.insert(a[u]);
    else treap.erase(a[u]);
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(v != p) addAll(v, u, val);
    }
}

void solve(int u, int p){
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(v != p && v != sc[u]){
            solve(v, u);
            addAll(v, u, -1);
        }
    }
    if(sc[u] != -1){
        solve(sc[u], u);
        for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(v != p && v != sc[u]) addAll(v, u, 1);
        }
    }
    treap.insert(a[u]);
    for(int i = 0; i < qry[u].size(); i++){
        int k = qry[u][i].first, id = qry[u][i].second;
        ans[id] = treap.kth(k);
    }
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int m;
        scanf("%d %d", &n, &m);
        treap.clear();
        for(int i = 1; i <= n; i++){
            adj[i].clear();
            qry[i].clear();
        }
        for(int i = 1; i <= n; i++){
            scanf("%d", &a[i]);
        }
        for(int i = 1; i < n; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(1, 1);
        for(int i = 0; i < m; i++){
            int x, k;
            scanf("%d %d", &x, &k);
            qry[x].push_back(mp(k, i));
        }
        solve(1, 1);
        for(int i = 0; i < m; i++){
            printf("%d ", ans[i]);
        }
        printf("\n");
    }

    return 0;
}
