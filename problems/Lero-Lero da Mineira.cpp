/*
Você receberá uma lista de regras de substituição que devem ser feitas em um texto. Cada regra é formada de uma letra e uma string correspondente pela qual a letra deve ser substituída. Depois disso, você receberá a string onde as regras devem ser aplicadas. Sempre que você encontrar nessa string um dos caracteres que devem ser substituídos de acordo com as regras recebidas, você deve fazer a substituição do caractere pela sua string correspondente, até que não seja mais possível mudar a string fazendo substituições deste tipo. Caso sempre haja uma mudança a ser feita, você deve avisar que é impossível terminar o processo.
*/
#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
#define x first
#define y second
using namespace std;

const int LS = 110, T = 1e5 + 10;

bool has[LS];
char s[26][LS], text[T];
bool adj[26][26];
int cnt[26];
string sub[26];

int main(){
	//freopen("in.txt", "r", stdin); // ~~~~~~~~~
	
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		char c;
		scanf(" %c", &c);
		int idx = c - 'a';
		has[idx] = true;
		scanf("%s", s[idx]);
		if(strlen(s[idx]) == 1 && s[idx][0] == c) has[idx] = false; // ~~~~~
	}
	for(int idx = 0; idx < 26; idx++) if(has[idx]){
		for(int i = 0; s[idx][i]; i++){
			int oidx = s[idx][i] - 'a';
			if(has[oidx] && !adj[oidx][idx]){
				adj[oidx][idx] = true;
				cnt[idx]++;
			}
		}
	}
	deque<int> dq;
	for(int idx = 0; idx < 26; idx++) if(has[idx] && !cnt[idx]){
		dq.push_back(idx);
	}
	while(!dq.empty()){
		int idx = dq.front(); dq.pop_front();
		for(int i = 0; i < 26; i++) if(has[i] && adj[idx][i]){
			if(--cnt[i] == 0) dq.push_back(i);
		}
		for(int i = 0; s[idx][i]; i++){
			int oidx = s[idx][i] - 'a';
			if(!has[oidx]) sub[idx] += s[idx][i];
			else sub[idx] += sub[oidx];
		}
	}
	
	int t;
	scanf("%d", &t);
	scanf("%s", text);
	
	for(int i = 0; i < t; i++){
		int idx = text[i] - 'a';
		if(cnt[idx]){
			printf("-1\n");
			return 0;
		}
	}
	
	string ans = "";
	for(int i = 0; i < t; i++){
		int idx = text[i] - 'a';
		if(!has[idx]) ans += text[i];
		else ans += sub[idx];
	}
	printf("%s\n", ans.c_str());
	return 0;
}
