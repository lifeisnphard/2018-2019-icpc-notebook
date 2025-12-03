/*
In this problem, you have to maintain a dynamic set of numbers which support the two fundamental operations

INSERT(S,x): if x is not in S, insert x into S
DELETE(S,x): if x is in S, delete x from S
and the two type of queries

K-TH(S) : return the k-th smallest element of S
COUNT(S,x): return the number of elements of S smaller than x
*/
#include <bits/stdc++.h>
using namespace std;

const int Q = 2e5 + 10;

pair<char, int> qry[Q];
int orig[Q], bit[Q];
bool is[Q];

void add(int pos, int val){
    for(int i = pos; i < Q; i += (i & -i)){
        bit[i] += val;
    }
}

int sum(int pos){
    int ret = 0;
    for(int i = pos; i >= 1; i -= (i & -i)){
        ret += bit[i];
    }
    return ret;
}

int kth(int k){
    int pos = 0;
    for(int i = 20; i >= 0; i--){
        if(pos + (1 << i) < Q && bit[pos + (1 << i)] < k){
            k -= bit[pos + (1 << i)];
            pos += (1 << i);
        }
    }
    return pos + 1;
}

int main(){
    int q;
    scanf("%d", &q);
    vector<int> all;
    for(int i = 0; i < q; i++){
        scanf(" %c %d", &qry[i].first, &qry[i].second);
        if(qry[i].first != 'K'){
            all.push_back(qry[i].second);
        }
    }
    sort(all.begin(), all.end());
    all.resize(unique(all.begin(), all.end()) - all.begin());
    for(int i = 0; i < q; i++) if(qry[i].first != 'K'){
        int tmp = qry[i].second;
        qry[i].second = 1 + lower_bound(all.begin(), all.end(), qry[i].second) - all.begin();
        orig[qry[i].second] = tmp;
    }
    for(int i = 0, qtd = 0; i < q; i++){
        if(qry[i].first == 'I'){
            if(!is[qry[i].second]){
                add(qry[i].second, 1);
                is[qry[i].second] = true;
                qtd++;
            }
        }else if(qry[i].first == 'D'){
            if(is[qry[i].second]){
                add(qry[i].second, -1);
                is[qry[i].second] = false;
                qtd--;
            }
        }else if(qry[i].first == 'C'){
            printf("%d\n", sum(qry[i].second - 1));
        }else{
            if(qry[i].second > qtd){
                printf("invalid\n");
            }else{
                printf("%d\n", orig[kth(qry[i].second)]);
            }
        }
    }
    return 0;
}
