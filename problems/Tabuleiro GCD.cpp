/*
Dado um grid infinito totalmente setado para o valor zero e Q queries dos tipos:

SET x y d: Seta a posição (x,y) do tabuleiro para o valor d

QUERY x y d: Retorna o gcd (Greatest Common Divisor) de todas as posições do tabuleiro que estão a uma distância de manhattan de no máximo d da posição (x,y).

0 <= |x|, |y| <= 500, 0 <= d <= 106
*/
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair

typedef long long ll;

int gcd(int a, int b){
    if(b == 0) return a;
    return gcd(b, a%b);
}

struct NodeY{
    int l, r, ans;

    NodeY(){}
    NodeY(int l, int r, int ans): l(l), r(r), ans(ans){}
};

struct NodeX{
    int l, r;
    vector<NodeY> nodeY;

    NodeX(){}
    NodeX(int l, int r): l(l), r(r){}
};
vector<NodeX> nodeX;

// Construindo a árvore ==========================================
void buildY(int segX, int seg, int l, int r){
    NodeY &node = nodeX[segX].nodeY[seg];
    node = NodeY(l, r, 0);
    if(l != r){
        int mid = (l + r)/2;
        buildY(segX, 2*seg + 1, l, mid);
        buildY(segX, 2*seg + 2, mid + 1, r);
    }
}

void buildX(int seg, int l, int r){
    nodeX[seg] = NodeX(l, r);
    if(l != r){
        int mid = (l + r)/2;
        buildX(2*seg + 1, l, mid);
        buildX(2*seg + 2, mid + 1, r);
    }
    nodeX[seg].nodeY.resize(2 * (1 << (int)ceil(log2(2000))));
    buildY(seg, 0, 0, 2000);
}


void build(){
    nodeX.resize(2 * (1 << (int)ceil(log2(2000))));
    buildX(0, 0, 2000);
}

// Update ========================================================
void updateY(int segX, int seg, int p, int val){
    NodeY &node = nodeX[segX].nodeY[seg];
    if(node.l > p || node.r < p) return;
    if(node.l == node.r){
        if(nodeX[segX].l == nodeX[segX].r) node.ans = val;
        else node.ans = gcd(nodeX[2*segX + 1].nodeY[seg].ans, nodeX[2*segX + 2].nodeY[seg].ans);
        return;
    }
    updateY(segX, 2*seg + 1, p, val);
    updateY(segX, 2*seg + 2, p, val);
    node.ans = gcd(nodeX[segX].nodeY[2*seg + 1].ans, nodeX[segX].nodeY[2*seg + 2].ans);
}

void updateX(int seg, int px, int py, int val){
    NodeX &node = nodeX[seg];
    if(node.l > px || node.r < px) return;
    if(node.l != node.r){
        updateX(2*seg + 1, px, py, val);
        updateX(2*seg + 2, px, py, val);
    }
    updateY(seg, 0, py, val);
}

// Query =========================================================
int queryY(int segX, int seg, int l, int r){
    NodeY &node = nodeX[segX].nodeY[seg];
    if(node.l > r || node.r < l) return 0;
    if(node.l >= l && node.r <= r) return node.ans;
    return gcd(queryY(segX, 2*seg + 1, l, r), queryY(segX, 2*seg + 2, l, r));
}

int queryX(int seg, int l, int r, int ly, int ry){
    NodeX &node = nodeX[seg];
    if(node.l > r || node.r < l) return 0;
    if(node.l >= l && node.r <= r) return queryY(seg, 0, ly, ry);
    return gcd(queryX(2*seg + 1, l, r, ly, ry), queryX(2*seg + 2, l, r, ly, ry));
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
    #endif

    int q;
    while(scanf("%d", &q) != EOF){
        build();
        while(q--){
            char str[10]; int tx, ty, d;
            scanf("%s %d %d %d", &str, &tx, &ty, &d);
            int x = tx + ty + 1000, y = ty - tx + 1000;
            if(!strcmp(str, "SET")){
                updateX(0, x, y, d);
            }else{
                int x1 = max(0, x - d), y1 = max(0, y - d);
                int x2 = min(2000, x + d), y2 = min(2000, y + d);
                printf("%d\n", queryX(0, x1, x2, y1, y2));
            }

        }
    }

    return 0;
}
