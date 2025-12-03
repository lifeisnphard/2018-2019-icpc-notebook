/*
O dispositivo tem uma fita com L células indexadas de 0 à L-1. Cada célula possui uma cor que pode ser alterado através dos comandos do dispositivo. Cada cor é codificada como um inteiro, e inicialmente todas as células possuem a mesma cor. As instruções que você encontrou representam N passos que devem ser executados antes do dispositivo mostrar o caminho do tesouro. Cada passo é descrito usando 4 inteiros P, X, A e B. As instruções dizem que para completar um passo você deve contar o número de células que atualmente possuem a cor P. Digamos que este número seja S. Então você deve calcular os valores

M1 = (A + S2 ) mod L ,

M2 = (A + (S + B)2 ) mod L .

Finalmente você deve fazer todas as células no intervalo fechado [min(M1,M2, max(M1,M2)] serem da cor de X.

Após essa exaustiva tarefa de processar os N passos requeridos pelo dispositivo, você tera ainda um trabalho: dada a cor que aparece o maior número de vezes no dispositivo após todos os passos (isto é, a cor mais frequente), você deve ir ao local do naufrágio do navio de Lyerpe e dizer em voz alta o número de celulas que possuem tal cor. Note que este número é único mesmo se mais de uma cor aparecer o maior número de vezes no dispositivo após todos os passos.
*/
#include <bits/stdc++.h>
using namespace std;
#define len(x) ((int)(x).size())

const int C = 1e5 + 10;

int qtd[C];
set<pair<pair<int, int>, int>> s;

inline void add_segment(int l, int r, int color){
    s.insert({{l, r}, color});
    qtd[color] += (r - l + 1);
}

inline void rmv_segment(int l, int r, int color){
    s.erase({{l, r}, color});
    qtd[color] -= (r - l + 1);
}

int main(){
	int n, c, q;
	scanf("%d %d %d", &n, &c, &q);
	add_segment(0, n - 1, 1);
	while(q--){
	    int p, x, a, b;
	    scanf("%d %d %d %d", &p, &x, &a, &b);
	    int qp = qtd[p];
	    int m1 = (a + qp*1LL*qp)%n, m2 = (a + (qp + b)*1LL*(qp + b))%n;
	    if(m1 > m2) swap(m1, m2);
	    
	    auto prev = s.upper_bound({{m1 - 1, n}, c});
	    if(prev != s.begin()){
	        prev--;
	        int l = prev->first.first, r = prev->first.second, color = prev->second;
	        if(r >= m1){
	            rmv_segment(l, r, color);
	            add_segment(l, m1 - 1, color);
	            
	            if(r > m2){
	                add_segment(m2 + 1, r, color);
	            }
	        }
	    }
	    
	    while(1){
	        auto it = s.lower_bound({{m1, 0}, 0});
	        if(it == s.end() || it->first.second > m2) break;
	        int l = it->first.first, r = it->first.second, color = it->second;
	        rmv_segment(l, r, color);
	    }
	    
	    auto nxt = s.lower_bound({{m1, 0}, 0});
	    if(nxt != s.end()){
	        int l = nxt->first.first, r = nxt->first.second, color = nxt->second; 
	        if(l <= m2){
	            rmv_segment(l, r, color);
	            add_segment(m2 + 1, r, color);
	        }
	    }
	    
	    add_segment(m1, m2, x);
	}
	int ans = 0;
	for(int i = 1; i <= c; i++){
	    ans = max(ans, qtd[i]);
	}
	printf("%d\n", ans);
	return 0;
}
