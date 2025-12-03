/*
Soma dos comprimentos das arestas do convex hull
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 2e3 + 10;

struct point{
    int x, y;

    point(){}
    point(int x, int y): x(x), y(y){}

    bool operator < (point b) const{
        return (x < b.x || (x == b.x && y < b.y));
    }

    point operator - (point b){
        return point(x - b.x, y - b.y);
    }
} p[N], pol[N];

int cross(point a, point b){
    return a.x*b.y - a.y*b.x;
}

int cross(point a, point b, point c){
    return cross(b - a, c - b);
}

double dist(point a, point b){
    int dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

int main(){
    int n;
    while(scanf("%d", &n) && n){
        for(int i = 0; i < n; i++){
            scanf("%d %d", &p[i].x, &p[i].y);
        }
        sort(p, p + n);
        int k = 0;
        for(int i = 0, mn = 2; i < n; i++){
            while(k >= mn && cross(pol[k - 2], pol[k - 1], p[i]) >= 0){
                k--;
            }
            pol[k++] = p[i];
        }
        for(int i = n - 2, mn = k + 1; i >= 0; i--){
            while(k >= mn && cross(pol[k - 2], pol[k - 1], p[i]) >= 0){
                k--;
            }
            pol[k++] = p[i];
        }
        double ans = 0;
        for(int i = 1; i < k; i++){
            ans += dist(pol[i - 1], pol[i]);
        }
        printf("Tera que comprar uma fita de tamanho %.2f.\n", ans);
    }
    return 0;
}
