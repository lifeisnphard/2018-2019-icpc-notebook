/*
Watson gives to Sherlock an array of N integers denoted by A1, A2 ... AN. 
Now he gives him Q queries of form Li, Ri. For each such query Sherlock has to report the number of inversions in subarray denoted by [Li, Ri].

Inversions in a subarray denoted by [a, b] are number of pairs (i, j) such that a ≤ i < j ≤ b and Ai > Aj.
*/
#include <bits/stdc++.h>
 
typedef long long ll;
 
using namespace std;
 
const int NQ = 1e5+10;
 
int n, sqn;
int a[NQ];
ll ans[NQ];
pair<int,int> tmp[NQ];
struct Qry{ int i, l, r; } qry[NQ];
 
// Comparators ======================================
bool bySecond(pair<int, int> v1, pair<int, int> v2){
    return (v1.second < v2.second);
}
 
bool qry_cmp(Qry q1, Qry q2){
    if(q1.l / sqn != q2.l / sqn){
        return (q1.l / sqn < q2.l / sqn);
    }
    return (q1.r < q2.r);
}
// ==================================================
 
struct Bit{
    ll node[NQ];
 
    void add(int pos, int v){
        if(!pos) return;
        for(int i = pos; i <= n; i += (i&-i)){
            node[i] += v;
        }
    }
 
    ll sum(int pos){
        ll ans = 0;
        for(int i = pos; i >= 1; i -= (i&-i)){
            ans += node[i];
        }
        return ans;
    }
 
    ll query(int a, int b){
        return sum(b) - sum(a - 1);
    }
} bit;
 
struct Mo{
    int curL, curR;
    ll curAns;
 
    ll query(int i){
        while(curL < qry[i].l){
            curAns -= bit.query(1, a[curL] - 1);
            bit.add(a[curL], -1);
            curL++;
        }
        while(curL > qry[i].l){
            curL--;
            curAns += bit.query(1, a[curL] - 1);
            bit.add(a[curL], 1);
        }
        while(curR < qry[i].r){
            curR++;
            curAns += bit.query(a[curR] + 1, n);
            bit.add(a[curR], 1);
        }
        while(curR > qry[i].r){
            curAns -= bit.query(a[curR] + 1, n);
            bit.add(a[curR], -1);
            curR--;
        }
        return curAns;
    }
} mo;
 
int main(){
    int q;
    scanf("%d %d", &n, &q);
    sqn = sqrt(n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        tmp[i] = make_pair(a[i], i);
    }
    // Compression ========================================
    sort(tmp + 1, tmp + n + 1);
    for(int i = 1; i <= n; i++){
        if(i > 1 && a[tmp[i - 1].second] == tmp[i].first){
            tmp[i].first = tmp[i - 1].first;
        }else tmp[i].first = i;
    }
    sort(tmp + 1, tmp + n + 1, bySecond);
    for(int i = 1; i <= n; i++){
        a[i] = tmp[i].first;
    }
    // ====================================================
 
    for(int i = 1; i <= q; i++){
        scanf("%d %d", &qry[i].l, &qry[i].r);
        qry[i].i = i;
    }
    sort(qry + 1, qry + q + 1, qry_cmp);
 
    for(int i = 1; i <= q; i++){
        ans[qry[i].i] = mo.query(i);
    }
 
    for(int i = 1; i <= q; i++){
        printf("%lld\n", ans[i]);
    }
 
    return 0;
}
