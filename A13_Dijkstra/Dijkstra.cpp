#include<bits/stdc++.h>
using namespace std;

const int INF = 0x7FFFFFFF;

class Graph{
private:
	struct edge{
		int v,w,nx;
	};
	struct node{
		int d,p;
		bool operator < (const node &o)const{
			return this->d > o.d;
		}
	};
	vector<edge> E;
	map<int, int> h, dis, pre;
public:
	void setVertex(int);
	Graph();
	Graph(const Graph &);
	Graph &operator = (Graph &);
	void Dijkstra(int);
	void addEdge(int, int, int);
	int getDistance(int);
	int getPreviousVertex(int);
	void clear();
	
};

Graph::Graph(){
	E.push_back((edge){0,0,0});
}

void Graph::clear(){
	E.clear();
	h.clear();
	dis.clear();
	pre.clear();
}

Graph::Graph(const Graph &x){
	E = x.E;
	h = x.h;
	dis = x.dis;
	pre = x.pre;
}

Graph &Graph::operator = (Graph &x){
	E = x.E;
	h = x.h;
	dis = x.dis;
	pre = x.pre;
	return *this;
}

void Graph::setVertex(int x){
	if(h.count(x) == 0)
		h[x] = 0;
}

void Graph::Dijkstra(int s){
	priority_queue<node> Q;
	map<int, bool> vis;
	for(auto &p : h){
		dis[p.first] = INF;
		pre[p.first] = 0;
		vis[p.first] = false;
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

void Graph::addEdge(int u, int v, int w){
	E.push_back((edge){v, w, h[u]});
	h[u] = (int)E.size() - 1;
}

int Graph::getDistance(int u){
	return dis[u];	
}

int Graph::getPreviousVertex(int u){
	return pre[u];
}

int n, m, s;
int main(){
	Graph G;
	scanf("%d%d%d", &n, &m ,&s);
	
	for(int i=1;i<=n;i++){
		G.setVertex(i);
	}
	
	for(int i=1;i<=m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		G.addEdge(a,b,c);
	}
	
	G.Dijkstra(s);
	
	puts("\ndis array");
	for(int i=1;i<=n;i++){
		printf("%d ", G.getDistance(i));
	}
	puts("");
	
	for(int i=1;i<=n;i++){
		printf("the shortest path to %d\n",i);
		int cur = i;
		while(cur != 0){
			printf("%d ",cur);
			cur = G.getPreviousVertex(cur);
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
