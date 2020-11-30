#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100050;
const int MAXM = 200050;
struct edge{
	int v,w,nx;
	
}E[MAXM];
int tot, h[MAXN];
void add_edge(int x, int y,int c){
	E[++tot] = (edge){y, c, h[x]};
	h[x] = tot;
}

struct node{
	int d,p;
	bool operator < (const node &o)const{
		return this->d > o.d;
	}
};
priority_queue<node> Q;
int dis[MAXN];
bool vis[MAXN];
void dij(int s){
	memset(dis, 0x7f, sizeof dis);
	memset(vis, 0, sizeof vis);
	dis[s] = 0;
	Q.push((node){0, s});
	while(!Q.empty()){
		node cur = Q.top();
		Q.pop();
		if(vis[cur.p])continue;
		vis[cur.p] = true;
		for(int i=h[cur.p];i;i=E[i].nx){
			int o = E[i].v;
			if(dis[o] > dis[cur.p] + E[i].w){
				dis[o] = dis[cur.p] + E[i].w;
				if(!vis[o]){
					Q.push((node){dis[o], o});
				}
			}
		}
	}
}
int n, m, s;
int main(){
	scanf("%d%d%d", &n, &m ,&s);
	for(int i=1;i<=m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
	}
	dij(s);
	for(int i=1;i<=n;i++){
		printf("%d ", dis[i]);
	}
	return 0;
}
