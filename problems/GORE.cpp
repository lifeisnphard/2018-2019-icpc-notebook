/*
Sua tarefa é, dada a localização de vários fornos numa fazenda, e uma distância D, determinar, para cada um dos fornos, quantos fornos estão à distância de manhattan de no máximo D.
*/
#include <bits/stdc++.h>
using namespace std;
 
#define mp make_pair
 
typedef long long ll;
 
const int N = 1e5 + 10, XY = 2e5 + 10;
 
pair<pair<int, int>, int> p[N];
int ans[N];
 
struct Bit{
    int bit[XY];
 
    void clear(){
        for(int i = 1; i < XY; i++){
            bit[i] = 0;
        }
    }
 
    void add(int pos, int val){
        for(int i = pos; i < XY; i += (i & -i)){
            bit[i] += val;
        }
    }
 
    void insert(pair<int, int> p){
        add(p.second, 1);
    }
 
    void erase(pair<int, int> p){
        add(p.second, -1);
    }
 
    int sum(int pos){
        int ans = 0;
        for(int i = pos; i >= 1; i -= (i & -i)){
            ans += bit[i];
        }
        return ans;
    }
 
    int query(int a, int b){
        return sum(b) - sum(a - 1);
    }
} bit;
 
int dist(pair<int, int> p1, pair<int, int> p2){
    return (abs(p1.first - p2.first) + abs(p1.second - p2.second));
}
 
int main(){
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
    #endif
 
    int tc;
    scanf("%d", &tc);
    while(tc--){
        int n, d;
        scanf("%d %d", &n, &d);
        for(int i = 1; i <= n; i++){
            int x, y;
            scanf("%d %d", &x, &y);
            p[i] = mp(mp(x + y + 1, y - x + 1e5 + 1), i);
            ans[i] = 0;
        }
        sort(p + 1, p + n + 1);
 
        // Calcula para a esquerda
        bit.insert(p[1].first);
        for(int i = 2, j = 1; i <= n; i++){
            while(j < i && p[i].first.first - p[j].first.first > d) bit.erase(p[j++].first);
            ans[p[i].second] += bit.query(max(0, p[i].first.second - d), min((int)2e5 + 1, p[i].first.second + d));
            bit.insert(p[i].first);
        }
        bit.clear();
 
        // Calcula para a direita
        bit.insert(p[n].first);
        for(int i = n - 1, j = n; i >= 1; i--){
            while(j > i && p[j].first.first - p[i].first.first > d) bit.erase(p[j--].first);
            ans[p[i].second] += bit.query(max(0, p[i].first.second - d), min((int)2e5 + 1, p[i].first.second + d));
            bit.insert(p[i].first);
        }
        bit.clear();
 
        printf("%d", ans[1]);
        for(int i = 2; i <= n; i++){
            printf(" %d", ans[i]);
        }
        printf("\n");
    }
 
    return 0;
}
