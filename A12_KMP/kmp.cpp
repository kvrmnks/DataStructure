#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
void build_next(char *str, int len, int *next){
	for(int i = 2; i <= len; i ++){
		int last = next[i - 1];
		while(last != 0 && str[last + 1] != str[i])
			last = next[last];
		
		next[i] = last;
		if(str[last + 1] == str[i])next[i] ++; 
	}
//	for(int i=1;i<=len;i++){
//		cout << next[i] << " "; 
//	}
//	cout << endl;
}

void find(char *s, int len_s, char *p, int *next, int len_p){
	int cur = 0;
	for(int i = 1; i <= len_s; i++){
		if(s[i] == p[cur + 1]) cur ++;
		else{
			int last = next[cur];
			while(last != 0 && p[last + 1] != s[i])
				last = next[last];
			cur = last;
			if(p[cur + 1] == s[i]) cur ++;
		}
		if(cur == len_p){printf("%d\n",i-len_p+1);cur = next[cur];}
	}
}

const int MAXN = 2000000;
char S[MAXN], P[MAXN];
int nx[MAXN], n, m;
int main(){
	scanf("%s", S + 1);
	scanf("%s", P + 1);
	n = strlen(S + 1);
	m = strlen(P + 1);
	build_next(P, m, nx);
	find(S, n, P, nx, m);
	for(int i=1;i<=m;i++){
		printf("%d ",nx[i]);
	}
	return 0;
}
