#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2000;
int n,m,rk[MAXN],data[MAXN],vis[MAXN];
int main(){
	

	
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d",data+i);
		rk[data[i]] ++;
		vis[data[i]] ++;
	}
	n = m + 2;
	cout << n - 1 <<endl;
	for(int i=1;i<=n;i++){
		rk[i] ++;
	}
	for(int i=1;i<=m;i++){
		int j = 0;
		for(j=1;j<=n;j++){
			if(vis[j] == 0 && rk[j]>0){
				break;
			}
		}
		cout << j << " " << data[i] << endl;
		vis[data[i]] --;
		rk[data[i]] --;
		rk[j] --;
	}
	int i = 1,j = n;
	while(rk[i]==0)i++;
	while(rk[j]==0)j--;
	cout << i<< " " << j <<endl;
	return 0;
}
