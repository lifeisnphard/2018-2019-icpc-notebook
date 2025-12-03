/*
That is, given an array a[1 ... n] of different integer numbers, your program must answer a series of questions Q(i, j, k) in the form: "What would be the k-th number in a[i ... j] segment, if this segment was sorted?"

For example, consider the array a = (1, 5, 2, 6, 3, 7, 4). Let the question be Q(2, 5, 3). The segment a[2 ... 5] is (5, 2, 6, 3). If we sort this segment, we get (2, 3, 5, 6), the third number is 5, and therefore the answer to the question is 5.
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

int arr[N];
pair<int, int> in[N];
vector<int> seg[4*N];

void build(int idx, int l, int r){
    int mid = (l + r)/2;
    if(l != r){
        build(2*idx + 1, l, mid);
        build(2*idx + 2, mid + 1, r);
    }
    inplace_merge(in + l, in + mid + 1, in + r + 1);
    for(int i = l; i <= r; i++){
        seg[idx].push_back(in[i].first);
    }
}

int qtd(int idx, int a, int b){
    return upper_bound(seg[idx].begin(), seg[idx].end(), b) - lower_bound(seg[idx].begin(), seg[idx].end(), a);
}

int query(int idx, int l, int r, int a, int b, int k){
    if(l == r) return arr[seg[idx][0]];
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
        scanf("%d", &arr[i]);
        in[i] = make_pair(arr[i], i);
    }
    sort(in + 1, in + n + 1);
    for(int i = 1; i <= n; i++){
        swap(in[i].first, in[i].second);
    }
    build(0, 1, n);
    for(int i = 0; i < m; i++){
        int a, b, k;
        scanf("%d %d %d", &a, &b, &k);
        printf("%d\n", query(0, 1, n, a, b, k));
    }
    return 0;
}
