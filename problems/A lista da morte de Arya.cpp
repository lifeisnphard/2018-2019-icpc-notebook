/*
A primeira linha contém um inteiro N (1 ≤ N ≤ 5×10^4), o número de inimigos inicialmente em sua lista.

Considere que todas as pessoas são numeradas de 1 a 10^9, inclusive. A próxima linha contém N inteiros, descrevendo a lista inicial de Arya. A próxima linha contém um inteiro Q (1 ≤ Q ≤ 5×10^4), o número de operações. As próximas Q linhas descrevem as operações. Cada operação pode estar em um dos seguintes formatos:

I p e (1 ≤ e, p ≤ 10^9): Insira a pessoa p depois do inimigo e na lista. É garantido que e está na lista, e p não está na lista;
R e (1 ≤ e ≤ 10^9): Remova o inimigo e da lista. É garantido que e está na lista;
Q a b (1 ≤ a, b ≤ 10^9): Determine quantos inimigos estão na lista entre a e b, excluindo ambos. É garantido que a e b estão na lista.
*/
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair

typedef long long ll;

const int N = 1e5, SQN = 316;

int qtd_blocks;
struct Block{
    vector<int> v;
    bool have[N + 10];

    // Complexity: O(sqrt(N))
    void clear(){ v.clear(); }

    // Complexity: O(1)
    int size(){ return v.size(); }

    // Complexity: O(1)
    void push_back(int val){
        v.push_back(val);
        have[val] = true;
    }

    // Complexity: O(1)
    int operator [](int p){ return v[p]; }

    // Complexity: O(sqrt(N))
    int find(int val){
        for(int i = 0; i < v.size(); i++){
            if(v[i] == val) return i;
        }
        return -1;
    }

    // Complexity: O(sqrt(N))
    void insert(int p, int e){
        vector<int>::iterator it = v.begin() + find(e);
        v.insert(it + 1, p);
        have[p] = true;
    }

    // Complexity: O(sqrt(N) + log(N))
    void erase(int val){
        v.erase(v.begin() + find(val));
        have[val] = false;
    }
} block[SQN + 10];

int find_block(int val){
    for(int i = 0; i < qtd_blocks; i++){
        if(block[i].have[val]) return i;
    }
    return -1;
}

int solve(int a, int b){
    if(a == b) return 0;

    int b1 = find_block(a), b2 = find_block(b);
    if(b1 > b2) return solve(b, a);

    int p1 = block[b1].find(a), p2 = block[b2].find(b);

    if(b1 == b2){
        if(p1 > p2) swap(p1, p2);
        return p2 - p1 - 1;
    }

    int ans = block[b1].size() - p1 - 1 + p2;
    for(int i = b1 + 1; i < b2; i++){
        ans += block[i].size();
    }
    return ans;
}

void rebuild(){
    vector<int> tmp;
    for(int i = 0; i < qtd_blocks; i++){
        for(int j = 0; j < block[i].size(); j++){
            tmp.push_back(block[i][j]);
            block[i].have[block[i][j]] = false;
        }
        block[i].clear();
    }
    qtd_blocks = (tmp.size() - 1)/SQN + 1;
    for(int i = 0; i < tmp.size(); i++){
        block[i/SQN].push_back(tmp[i]);
    }
}

int ncnt;
map<int, int> comp;

int num(int val){
    if(!comp[val]) comp[val] = ++ncnt;
    return comp[val];
}

int main(){
    int n;
    scanf("%d", &n);
    qtd_blocks = (n - 1)/SQN + 1;
    for(int i = 0; i < n; i++){
        int x;
        scanf("%d", &x);
        block[i/SQN].push_back(num(x));
    }
    int q;
    scanf("%d", &q);
    for(int i = 0, cnt = 0; i < q; i++){
        char t;
        scanf(" %c", &t);
        if(t == 'I'){
            int p, e;
            scanf("%d %d", &p, &e);
            p = num(p), e = num(e);
            block[find_block(e)].insert(p, e);
            if(++cnt%SQN == 0) rebuild();
        }else if(t == 'R'){
            int e;
            scanf("%d", &e);
            e = num(e);
            block[find_block(e)].erase(e);
        }else{
            int a, b;
            scanf("%d %d", &a, &b);
            a = num(a), b = num(b);
            printf("%d\n", solve(a, b));
        }
    }
    return 0;
}
