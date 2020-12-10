#include<vector>
#include<map>
#include<iostream>
#include<algorithm>
class Graph{
private:
	struct Edge{
		int from, to, cost;
	};
	std::map<int ,std::vector<std::pair<int, int>>> G;
	class UnionFindSet{
	private:
		std::map<int, int> ufs, height;
	public:
		void setSet(int x){ufs[x] = x; height[x] = 0;}
		void removeSet(int x){
			if(ufs.count(x) > 0){
				ufs.erase(x);
				height.erase(x);
			}
		}	
		int find(int x){
			return ufs[x] == x ? x : ufs[x] = find(ufs[x]);
		}
		void merge(int x, int y){
			x = find(x);
			y = find(y);
			if(x == y)return;
			if(height[x] > height[y]) std::swap(x, y);
			if(height[x] == height[y]){
				height[x] ++;
				ufs[y] = x;
			}else{
				ufs[x] = y;
			}
		}
		bool disjoint(int x,int y){
			return find(x) != find(y);
		}
		void clear(){
			ufs.clear();
			height.clear();
		}
	};
	bool isCut(std::map<int, int> &_head, std::vector<Edge> &_edge, int id){
		UnionFindSet uf;
		for(auto &x : _head)uf.setSet(x.first);
		for(int i=2;i<(int)_edge.size();i++){
			if(id == i || _edge[i].cost == 1)continue;
			uf.merge(_edge[i].from, _edge[i].to);
		}
		return uf.disjoint(_edge[id].from, _edge[id].to);
	}
public:
	void setVertex(int x){
		if(G.count(x) == 0)
			G[x] = {};
	}
	void addEdge(int x, int y,int v){
		G[x].push_back(std::make_pair(y, v));
		G[y].push_back(std::make_pair(x, v));
	}
	bool kruskal(std::vector<std::pair<int ,std::pair<int, int>>> &out){
		std::vector<Edge> edge;
		UnionFindSet uf;
		for(auto &x : G){
			uf.setSet(x.first);
			for(auto &y : x.second){
				edge.push_back({x.first, y.first, y.second});
			}
		}
		std::sort(edge.begin(), edge.end(), [](Edge &x, Edge &y)->int{
			return x.cost < y.cost;
		});
		int partialCounter = 0;
		for(auto &x : edge){
			if(uf.disjoint(x.from, x.to)){
				uf.merge(x.from, x.to);
				out.push_back(std::make_pair(x.cost, std::make_pair(x.from, x.to)));
				partialCounter++;
			}
		}
		return partialCounter == (int)G.size() - 1;
	}
	
	bool fleury(std::vector<std::pair<int, int>> &out){
		//must be only 1 connected component  
		for(auto &x : G) if((int)x.second.size() & 1) return false;
		std::vector<Edge> _edge;
		_edge.push_back({});
		_edge.push_back({});
		std::map<int, int> _head, _next;
		for(auto &x : G)
			for(auto &y : x.second){
				if(x.first > y.first) continue;
				_edge.push_back({x.first, y.first, 0});
				_next[(int)_edge.size() - 1] = _head[x.first];
				_head[x.first] = (int)_edge.size() - 1;
				
				_edge.push_back({y.first, x.first, 0});
				_next[(int)_edge.size() - 1] = _head[y.first];
				_head[y.first] = (int)_edge.size() - 1;				
			}
		int edgeCnt = 0;
		int curVertex = G.begin()->first;
		while(edgeCnt != (int)_edge.size()){
			int partialCnt = 0;
			int pos = -1;
			for(int i=_head[curVertex]; i; i = _next[i]){
				partialCnt += (_edge[i].cost == 0);
				if(_edge[i].cost == 0)pos = i;
			}
			if(partialCnt == 0){
				break;
			}else if(partialCnt == 1){
				out.push_back(std::make_pair(_edge[pos].from, _edge[pos]. to));
				_edge[pos].cost = _edge[pos^1].cost = 1;
				curVertex = _edge[pos].to;
			}else{
				int pos = -1;
				for(int i=_head[curVertex]; i; i = _next[i])if(_edge[i].cost == 0 && !isCut(_head, _edge, i)){
					pos = i;
					break;
				}
				out.push_back(std::make_pair(_edge[pos].from, _edge[pos]. to));
				_edge[pos].cost = _edge[pos^1].cost = 1;
				curVertex = _edge[pos].to;				
			}
			edgeCnt ++;
		}
		return true;
	}
};

#include<iostream>
int main(){
	int n, m;
	scanf("%d%d", &n,&m);
	Graph g;
	for(int i=1;i<=n;i++){g.setVertex(i);}
	for(int i=1;i<=m;i++){
		int a,b,c;
		scanf("%d%d%d", &a, &b, &c);
		g.addEdge(a, b, c);
	}
	std::vector<std::pair<int, std::pair<int ,int>>> ans1;
	std::vector<std::pair<int,int>>ans2;
	g.kruskal(ans1);
	g.fleury(ans2);
	std::cout << "Eulerian circuit\n";
	for(auto &x : ans2){
		std::cout <<"edge from "<< x.first << "  to " << x.second << std::endl;
	}
	std::cout << "Minimum spanning tree\n";
	for(auto &x : ans1){
		std::cout << "edge from " << x.second.first << " to " << x.second.second << " with distance " << x.first << " \n";
	}
	int sum = 0;
	for(auto &x : ans1){
		sum += x.first;
	}
	std::cout << "total cost "<< sum;
	return 0;
}

/*
7 8
1 2 3
2 3 4
1 4 1
4 3 5
3 5 6
5 6 1
3 7 2
6 7 3
     
(x) -> vertex

....    -> a edge with distance y
  y
  
  
       (2)             (5)
    .     . 4       .     .
  .  3      .    .   6      . 1
(1)           (3)             (6)
  .          .  .          . 3
    .1     .      . 2    .
       (4)   5        (7)
       
*/
