/*
That is, given an array a[1 ... n] of different integer numbers, your program must answer a series of questions Q(i, j, k) in the form: "What would be the k-th number in a[i ... j] segment, if this segment was sorted?"

For example, consider the array a = (1, 5, 2, 6, 3, 7, 4). Let the question be Q(2, 5, 3). The segment a[2 ... 5] is (5, 2, 6, 3). If we sort this segment, we get (2, 3, 5, 6), the third number is 5, and therefore the answer to the question is 5.
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

pair<int, int> v[N];
vector<pair<int, int> > seg[4*N];

void build(int idx, int l, int r){
    int mid = (l + r)/2;
    if(l != r){
        build(2*idx + 1, l, mid);
        build(2*idx + 2, mid + 1, r);
    }
    inplace_merge(v + l, v + mid + 1, v + r + 1);
    for(int i = l; i <= r; i++){
        seg[idx].push_back(v[i]);
    }
}

int qtd(int idx, int a, int b){
    return upper_bound(seg[idx].begin(), seg[idx].end(), make_pair(b, INT_MAX)) - lower_bound(seg[idx].begin(), seg[idx].end(), make_pair(a, INT_MIN));
}

int query(int idx, int l, int r, int a, int b, int k){
    if(l == r) return seg[idx][0].second;
    int mid = (l + r)/2, qtdL = qtd(2*idx + 1, a, b);
    if(qtdL >= k){
        return query(2*idx + 1, l, mid, a, b, k);
    }else{
        return query(2*idx + 2, mid + 1, r, a, b, k - qtdL);
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &v[i].first);
        v[i].second = i;
    }
    sort(v + 1, v + n + 1);
    for(int i = 1; i <= n; i++){
        swap(v[i].first, v[i].second);
    }
    build(0, 1, n);
    for(int i = 0; i < m; i++){
        int a, b, k;
        scanf("%d %d %d", &a, &b, &k);
        printf("%d\n", query(0, 1, n, a, b, k));
    }
    return 0;
}
