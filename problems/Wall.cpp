/*
Jian-Jia is building a wall by stacking bricks of the same size ogether. This wall consists of n columns of bricks, which are numbered 0 to n − 1 from left to right. The columns may have different heights. The height of a column is the number of bricks in it.

Jian-Jia builds the wall as follows. Initially there are no bricks in any column. Then, Jian-Jia goes through k phases of adding or removing bricks. The building process completes when all k phases are finished. In each phase Jian-Jia is given a range of consecutive brick columns and a height h, and he does the following procedure:

In an adding phase, Jian-Jia adds bricks to those columns in the given range that have less than h bricks, so that they have exactly h bricks. He does nothing on the columns having h or more bricks.
In a removing phase, Jian-Jia removes bricks from those columns in the given range that have more than h bricks, so that they have exactly h bricks. He does nothing on the columns having h bricks or less.
Your task is to determine the final shape of the wall.
*/
//#include "grader.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 10;

int a[N], hmin[4*N], hmax[4*N];

void build(int idx, int l, int r){
    hmin[idx] = -1;
    hmax[idx] = 1e9;
    if(l != r){
        int mid = (l + r)/2;
        build(2*idx + 1, l, mid);
        build(2*idx + 2, mid + 1, r);
    }
}

void upd_hmin(int idx, int h){
    hmin[idx] = max(hmin[idx], h);
    if(hmax[idx] != 1e9 && hmax[idx] < hmin[idx]){
        hmax[idx] = hmin[idx];
    }
}

void upd_hmax(int idx, int h){
    hmax[idx] = min(hmax[idx], h);
    if(hmin[idx] != -1 && hmin[idx] > hmax[idx]){
        hmin[idx] = hmax[idx];
    }
}

void upd(int idx, int l, int r){
    if(hmin[idx] != -1){
        if(l == r){
            if(a[l] < hmin[idx]){
                a[l] = hmin[idx];
            }
        }else{
            upd_hmin(2*idx + 1, hmin[idx]);
            upd_hmin(2*idx + 2, hmin[idx]);
        }
        hmin[idx] = -1;
    }
    if(hmax[idx] != 1e9){
        if(l == r){
            if(a[l] > hmax[idx]){
                a[l] = hmax[idx];
            }
        }else{
            upd_hmax(2*idx + 1, hmax[idx]);
            upd_hmax(2*idx + 2, hmax[idx]);
        }
        hmax[idx] = 1e9;
    }
}

void add(int idx, int l, int r, int a, int b, int h){
    upd(idx, l, r);
    if(l > b || r < a) return;
    if(l >= a && r <= b){
        upd_hmin(idx, h);
        upd(idx, l, r);
        return;
    }
    int mid = (l + r)/2;
    add(2*idx + 1, l, mid, a, b, h);
    add(2*idx + 2, mid + 1, r, a, b, h);
}

void rmv(int idx, int l, int r, int a, int b, int h){
    upd(idx, l, r);
    if(l > b || r < a) return;
    if(l >= a && r <= b){
        upd_hmax(idx, h);
        upd(idx, l, r);
        return;
    }
    int mid = (l + r)/2;
    rmv(2*idx + 1, l, mid, a, b, h);
    rmv(2*idx + 2, mid + 1, r, a, b, h);
}

int query(int idx, int l, int r, int pos){
    upd(idx, l, r);
    if(l == r) return a[l];
    int mid = (l + r)/2;
    if(pos <= mid){
        return query(2*idx + 1, l, mid, pos);
    }else{
        return query(2*idx + 2, mid + 1, r, pos);
    }
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
    build(0, 0, n - 1);
    for(int i = 0; i < k; i++){
        if(op[i] == 1){
            add(0, 0, n - 1, left[i], right[i], height[i]);
        }else{
            rmv(0, 0, n - 1, left[i], right[i], height[i]);
        }
    }
    for(int i = 0; i < n; i++){
        finalHeight[i] = query(0, 0, n - 1, i);
    }
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int *op = new int[k], *left = new int[k], *right = new int[k], *height = new int[k];
    for(int i = 0; i < k; i++){
        scanf("%d %d %d %d", &op[i], &left[i], &right[i], &height[i]);
    }
    int *finalHeight = new int[n];
    buildWall(n, k, op, left, right, height, finalHeight);
    for(int i = 0; i < n; i++){
        printf("%d\n", finalHeight[i]);
    }
    return 0;
}
