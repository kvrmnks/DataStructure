#include<bits/stdc++.h>
using namespace std;
struct edge{
	int v,w,nx;
};
edge *E;
int tot, *h, *pre;
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
int *dis;
bool *vis;
int n, m, s;
void dij(int s){
	for(int i=1;i<=n;i++){
		dis[i] = 0x7fffffff;
		vis[i] = false;
	}
	dis[s] = 0;
	pre[s] = 0;
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
				pre[o] = cur.p;
				if(!vis[o]){
					Q.push((node){dis[o], o});
				}
			}
		}
	}
}

int main(){
	scanf("%d%d%d", &n, &m ,&s);
	h = new int[n+1];
	for(int i=1;i<=n;i++)h[i]=0;
	E = new edge[m+1];
	dis = new int[n+1];
	vis = new bool[n+1];
	pre = new int[n+1];
	for(int i=1;i<=m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
	}
	dij(s);
	for(int i=1;i<=n;i++){
		printf("%d ", dis[i]);
	}
	puts("");
	for(int i=1;i<=n;i++){
		printf("第%d点的最短路径\n",i);
		int cur = i;
		while(cur != 0){
			printf("%d ",cur);
			cur = pre[cur];
		}
		puts("");
	}
	return 0;
}
/*
test case
4 6 1
1 2 2
2 3 2
2 4 1
1 3 5
3 4 3
1 4 4

*/
