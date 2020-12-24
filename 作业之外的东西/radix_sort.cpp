#include<bits/stdc++.h>
using namespace std;
int read(){
	int rt=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch = getchar();
	while(ch>='0' && ch<='9'){rt = rt * 10 + ch-'0'; ch = getchar();}
	return rt;
}
const int MAXN = 100050;
const int P = 15;
int reminder[1 << P], data[2][MAXN];
int main(){
	int n;
	n = read();
	for(int i=1;i<=n;i++){
		data[0][i] = read();
	}
	int t=0,p=0;
	while(t <= 1){
		for(int i=0; i< (1<<P);i++)reminder[i] = 0;
		for(int i=1;i<=n;i++){
			int tmp = ((1 << P) - 1) & (data[p][i] >> (t * P));
			reminder[tmp] ++;
		}
		for(int i=1;i<(1<<P);i++){
			reminder[i] += reminder[i-1];
		}
		for(int i=n;i>=1;i--){
			int tmp = ((1 << P) - 1) & (data[p][i] >> (t * P));
			data[p^1][reminder[tmp]--] = data[p][i];
		}
		p^=1;
		t++;
	}
	for(int i=1;i<n;i++){
		printf("%d ",data[p][i]);
	}
	printf("%d",data[p][n]);
	return 0;
}
