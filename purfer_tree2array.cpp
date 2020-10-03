#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10000;
int h[MAXN], nx[MAXN<<1], to[MAXN<<1], tot, rk[MAXN];
int vis[MAXN], arr[MAXN], pcnt;
void add_edge(int x, int y){
	nx[++tot] = h[x];
	h[x] = tot;
	to[tot] = y;
	rk[y] ++;
}
void link(int x,int y){
	add_edge(x,y);
	add_edge(y,x);
}
int n;
int main(){
	freopen("purfer.in", "r", stdin);
	cin >> n;
	for(int i=1;i<n;i++){
		int a, b;
		cin >> a >> b;
		link(a, b);
	}
	priority_queue<int, vector<int>, greater<int> > Q;
	for(int i=1;i<=n;i++){
		if(rk[i] == 1){
			Q.push(i);
			vis[i] = 1;
		}
	}
	int cnt = 0;
	while(cnt + 2 <= n){
		int x = Q.top();
		Q.pop();
		cnt ++;
		for(int j=h[x];j;j=nx[j]){
			if(vis[to[j]])
				continue;
			arr[++pcnt] = to[j];
			rk[to[j]] -- ;
			if(rk[to[j]] == 1){
				vis[to[j]] = 1;
				Q.push(to[j]);
			}
		}
	}
	for(int i=1;i<=pcnt;i++){
		cout << arr[i] << " ";
	}
	return 0;
}
