/*
Given an array having N elements, each element is either -1 or 1.

You have M queries, each query has two numbers L and R, you have to answer the length of the longest subarray in range L to R (inclusive) that its sum is equal to 0.
*/
#include <bits/stdc++.h>
using namespace std;
 
const int NM = 5e4 + 10, SQRTN = 230;
 
int sum[NM], ans[NM];
vector<pair<pair<int, int>, int> > qry[SQRTN];
deque<int> pos[2*NM];
 
int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        int x;
        scanf("%d", &x);
        sum[i] = sum[i - 1] + x;
    }
    for(int i = 0; i <= n; i++){
        sum[i] += n;
        assert(sum[i] >= 0 && sum[i] < 2*NM);
    }
    n++; // Queries: [0, n]
    int sqrtn = sqrt(n);
    for(int i = 0; i < m; i++){
        int l, r;
        scanf("%d %d", &l, &r); l--;
        qry[l/sqrtn].push_back(make_pair(make_pair(r, l), i));
    }
    for(int i = 0; i <= (n - 1)/sqrtn; i++){
        sort(qry[i].begin(), qry[i].end());
        int nxt = (i + 1)*sqrtn, curAns = 0;
        for(int j = 0; j < qry[i].size(); j++){
            int l = qry[i][j].first.second, r = qry[i][j].first.first, idx = qry[i][j].second;
            while(nxt <= r){
                pos[sum[nxt]].push_back(nxt);
                curAns = max(curAns, pos[sum[nxt]].back() - pos[sum[nxt]].front());
                nxt++;
            }
            int tmp = curAns;
            for(int k = min((i + 1)*sqrtn - 1, r); k >= l; k--){
                pos[sum[k]].push_front(k);
                tmp = max(tmp, pos[sum[k]].back() - pos[sum[k]].front());
            }
            ans[idx] = tmp;
            for(int k = l; k <= min((i + 1)*sqrtn - 1, r); k++){
                pos[sum[k]].pop_front();
            }
        }
        for(int j = (i + 1)*sqrtn; j < nxt; j++){
            pos[sum[j]].pop_front();
        }
    }
    for(int i = 0; i < m; i++){
        printf("%d\n", ans[i]);
    }
    return 0;
}
