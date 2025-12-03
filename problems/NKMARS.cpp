/*
In the year 2051, several Mars expeditions explored different areas of the red planet and produced maps of these areas. Now, the BaSA (Baltic Space Agency) has an ambitious plan: they would like to produce a map of the whole planet. In order to calculate the necessary effort, they need to know the total size of the area for which maps already exist. It is your task to write a program that calculates this area.

Input
The input starts with a line containing a single integer N (1 ≤ N ≤ 10 000 ), the number of available maps. Each of the following N lines describes a map. Each of these lines contains four integers x1, y1, x2 and y2 (0 ≤ x1 < x2 ≤ 30 000 , 0 ≤ y1 < y2 ≤ 30 000 ). The values ( x1;y1) and ( x2;y2) are the coordinates of, respectively, the bottom-left and the top- right corner of the mapped area. Each map has rectangular shape, and its sides are parallel to the x- and y-axis of the coordinate system.
*/
#include <bits/stdc++.h>
using namespace std;

const int T = 3e4 + 10;

struct event{
    int x, y1, y2, t;

    event(int x = 0, int y1 = 0, int y2 = 0, int t = 0): x(x), y1(y1), y2(y2), t(t){}

    bool operator < (event b) const{
        return (x < b.x);
    }
};

int seg[4*T], cov[4*T];

void upd(int idx, int l, int r, int a, int b, int val){
    if(l > b || r < a) return;
    if(l >= a && r <= b){
        cov[idx] += val;
    }else{
        int mid = (l + r)/2;
        upd(2*idx + 1, l, mid, a, b, val);
        upd(2*idx + 2, mid + 1, r, a, b, val);
    }
    if(cov[idx]){
        seg[idx] = r - l + 1;
    }else if(l == r){
        seg[idx] = 0;
    }else{
        seg[idx] = seg[2*idx + 1] + seg[2*idx + 2];
    }
}

int main(){
    int n;
    scanf("%d", &n);
    vector<event> events;
    for(int i = 0, x1, y1, x2, y2; i < n; i++){
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        events.push_back(event(x1, y1, y2, 1));
        events.push_back(event(x2, y1, y2, -1));
    }
    sort(events.begin(), events.end());
    int ans = 0, lastX = 0;
    for(int i = 0; i < events.size(); i++){
        int x = events[i].x, y1 = events[i].y1, y2 = events[i].y2, t = events[i].t;
        ans += seg[0]*(x - lastX);
        upd(0, 0, 3e4, y1 + 1, y2, t);
        lastX = x;
    }
    printf("%d\n", ans);
    return 0;
}
