/*
Line-Sweep to offline checking of several points if they are inside or outside of a axis-parallel polygon.
*/
#include <bits/stdc++.h>
using namespace std;

const int PV = 1e5 + 10;

int bit[PV];

void add(int i, int val){
    for(; i < PV; i += (i & -i)){
        bit[i] += val;
    }
}

int sum(int i){
    int ret = 0;
    for(; i >= 1; i -= (i & -i)){
        ret += bit[i];
    }
    return ret;
}

int main(){
    int p, v;
    scanf("%d %d", &p, &v);
    vector<pair<pair<int, int>, int> > plant(p);
    for(int i = 0, x, y; i < p; i++){
        scanf("%d %d", &x, &y);
        plant[i] = make_pair(make_pair(x, y), i);
    }
    vector<pair<int, int> > vert(v);
    for(int i = 0, x, y; i < v; i++){
        scanf("%d %d", &x, &y);
        vert[i] = make_pair(x, y);
    }

    vector<int> cy(p + v);
    for(int i = 0; i < p; i++){
        cy[i] = plant[i].first.second;
    }
    for(int i = 0; i < v; i++){
        cy[p + i] = vert[i].second;
    }
    sort(cy.begin(), cy.end());
    cy.resize(unique(cy.begin(), cy.end()) - cy.begin());
    for(int i = 0; i < p; i++){
        plant[i].first.second = 1 + lower_bound(cy.begin(), cy.end(), plant[i].first.second) - cy.begin();
    }
    for(int i = 0; i < v; i++){
        vert[i].second = 1 + lower_bound(cy.begin(), cy.end(), vert[i].second) - cy.begin();
    }

    vector<pair<int, pair<int, int> > > side;
    for(int i = 0; i < v; i++){
        int nxt = (i + 1)%v;
        if(vert[i].first == vert[nxt].first){
            int x = vert[i].first, ya = vert[i].second, yb = vert[nxt].second;
            side.push_back(make_pair(x, make_pair(min(ya, yb), max(ya, yb))));
        }
    }

    sort(plant.begin(), plant.end());
    sort(side.begin(), side.end());

    long long ans = 0;
    for(int i = 0, j = 0; i < plant.size(); i++){
        for(; j < side.size() && side[j].first <= plant[i].first.first; j++){
            add(side[j].second.first + 1, 1);
            add(side[j].second.second + 1, -1);
        }
        if(sum(plant[i].first.second)%2 == 0){
            ans += plant[i].second + 1;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
