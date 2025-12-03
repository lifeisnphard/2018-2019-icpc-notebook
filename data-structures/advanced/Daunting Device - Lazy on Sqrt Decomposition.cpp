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

const int NC = 1e5 + 10, SQRTN = 320;

vector<int> seg[SQRTN];
int qtd[SQRTN][NC], lazy[SQRTN], qtd_tot[NC];

void upd(int idx){
	if(lazy[idx]){
		for(int i = 0; i < len(seg[idx]); i++){
			qtd[idx][seg[idx][i]]--;
			seg[idx][i] = lazy[idx];
			qtd[idx][seg[idx][i]]++;
		}
		lazy[idx] = 0;
	}
}

int main(){
	int n, c, m;
	scanf("%d %d %d", &n, &c, &m);
	for(int i = 0; i < n; i++){
		int b = i/SQRTN;
		seg[b].push_back(1);
		qtd[b][1]++;
	}
	while(m--){
		int p, x, a, b;
		scanf("%d %d %d %d", &p, &x, &a, &b);
		
		int s = 0;
		for(int i = 0; i < SQRTN; i++){
			if(lazy[i]) s += ((lazy[i] == p)? len(seg[i]) : 0);
			else s += qtd[i][p];
		}
		
		int l = (a + s*1LL*s)%n, r = (a + (s + b)*1LL*(s + b))%n;
		if(l > r) swap(l, r);
		
		int bl = l/SQRTN, pl = l%SQRTN;
		int br = r/SQRTN, pr = r%SQRTN;
		
		if(bl == br){
			upd(bl);
			for(int i = pl; i <= pr; i++){
				qtd[bl][seg[bl][i]]--;
				seg[bl][i] = x;
				qtd[bl][seg[bl][i]]++;
			}
		}else{
			upd(bl);
			for(int i = pl; i < len(seg[bl]); i++){
				qtd[bl][seg[bl][i]]--;
				seg[bl][i] = x;
				qtd[bl][seg[bl][i]]++;
			}
			
			for(int i = bl + 1; i < br; i++){
				lazy[i] = x;
			}
			
			upd(br);
			for(int i = 0; i <= pr; i++){
				qtd[br][seg[br][i]]--;
				seg[br][i] = x;
				qtd[br][seg[br][i]]++;
			}
		}
	}
	for(int i = 0; i < SQRTN; i++){
		upd(i);
		for(int j = 1; j <= c; j++) qtd_tot[j] += qtd[i][j];
	}
	int ans = 0;
	for(int i = 1; i <= c; i++){
		ans = max(ans, qtd_tot[i]);
	}
	printf("%d\n", ans);
	return 0;
}
