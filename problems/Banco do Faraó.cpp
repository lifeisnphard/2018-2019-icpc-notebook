/*
Queries kadane-style on segments of an array.
*/
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 1e5 + 10;

int a[N];

struct Range{
    int sum, len;

    Range(){}
    Range(int sum, int len): sum(sum), len(len){}

    Range operator + (Range b){ return Range(sum + b.sum, len + b.len); }
};

Range maxRange(Range a, Range b){
    if(a.sum > b.sum || (a.sum == b.sum && a.len > b.len)) return a;
    return b;
}

struct Ans{
    Range all, left, right, best;

    Ans(){}
    Ans(int sum, int len): all(Range(sum, len)), left(Range(sum, len)), right(Range(sum, len)), best(Range(sum, len)){}
};

Ans combine(Ans a, Ans b){
    if(a.all.sum == -INF) return b;
    if(b.all.sum == -INF) return a;
    Ans comb;
    comb.all = a.all + b.all;
    comb.left = maxRange(a.left, a.all + b.left);
    comb.right = maxRange(a.right + b.all, b.right);
    comb.best = maxRange(a.right + b.left, maxRange(a.best, b.best));
    return comb;
}

struct Node{
    int l, r;
    Ans ans;

    Node(){}
    Node(int l, int r): l(l), r(r){}
} node[4*N];

void build_tree(int seg, int l, int r){
    node[seg] = Node(l, r);
    if(l == r){
        node[seg].ans = Ans(a[l], 1);
    }else{
        int mid = (l + r)/2;
        build_tree(2*seg + 1, l, mid);
        build_tree(2*seg + 2, mid + 1, r);
        node[seg].ans = combine(node[2*seg + 1].ans, node[2*seg + 2].ans);
    }
}

Ans query(int seg, int l, int r){
    if(node[seg].l > r || node[seg].r < l) return Ans(-INF, 0);
    if(node[seg].l >= l && node[seg].r <= r) return node[seg].ans;
    return combine(query(2*seg + 1, l, r), query(2*seg + 2, l, r));
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++){
            scanf("%d", &a[i]);
        }
        build_tree(0, 1, n);
        int q;
        scanf("%d", &q);
        while(q--){
            int a, b;
            scanf("%d %d", &a, &b);
            Ans ans = query(0, a, b);
            printf("%d %d\n", ans.best.sum, ans.best.len);
        }
    }
    return 0;
}
